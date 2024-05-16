#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <cassert>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"


/**
 * reads a file and outputs it as a string.
 *
 * \param filepath path to the file
 * \return string of file contents
 */
static std::string readShaderFile(const std::string& filepath) {

	std::ifstream file(filepath);
	if (!file.is_open()) {
		std::cout << "Failed to open file: " << filepath << std::endl;
	}

	std::string content;
	std::string line;

	while (std::getline(file, line)) {
		content += line + "\n";
	}

	return content;
}

/**
 * given the shader directory it reads shader programs returns them both as strings.
 *
 * \param directory path to the directory containing the shader files
 * \return the pair of vertex and fragment shader strings
 */
static std::pair<std::string, std::string> parseShaderFiles(const std::string& directory) {
	std::string fragmentShader;
	std::string vertexShader;

	for (const auto& file : std::filesystem::directory_iterator(std::filesystem::absolute(directory))) {
		if (file.path().extension() == ".frag") {
			fragmentShader = readShaderFile(file.path().string());
		}
		else if (file.path().extension() == ".vert") {
			vertexShader = readShaderFile(file.path().string());
		}
	}

	return { vertexShader, fragmentShader };
}

/**
 * compiles opengl shader program and returns a refrence to it.
 *
 * \param type type of shader
 * \param source shader source code
 * \return refrence to shader
 */
static unsigned int complileShader(unsigned int type, const std::string& source) {
	std::cout << "Compiling " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader..." << std::endl;
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//do error handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)malloc(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

/**
 * compiles and attaches shaders to opengl.
 *
 * \param vertexShader
 * \param fragementShader
 * \return shader program
 */
static unsigned int createShader(const std::string& vertexShader, const std::string& fragementShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = complileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = complileShader(GL_FRAGMENT_SHADER, fragementShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int main(void) {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "OpenGL", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(4);

	//init glew and check for errors
	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	//print the version of OpenGL
	std::cout << glGetString(GL_VERSION) << std::endl;

	//enable debug output
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(MessageCallback, 0);

	float positions[] = {
		-0.5f, -0.5f, //0
		 0.5f, -0.5f, //1
		 0.5f,  0.5f, //2
		-0.5f,  0.5f, //3
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};


	//create vertex array and bind
	VertexArray va;
	//create vertex buffer and bind while the vao is still bound
	VertexBuffer vb(positions, 4 * 2 * sizeof(float));

	//create layout and add buffer to vertex array
	VertexBufferLayout layout;
	layout.push<float>(2);
	va.AddBuffer(vb, layout);

	//create index buffer and bind while the vao is still bound
	IndexBuffer ib(indices, 6);

	//parse shader files and create shader
	std::pair<std::string, std::string> shaders = parseShaderFiles("res/shaders");
	int shader = createShader(shaders.first, shaders.second);
	glUseProgram(shader);

	int location = glGetUniformLocation(shader, "u_Color");
	assert(location != -1);
	glUniform4f(location, 0.2f, 0.8f, 1.0f, 1.0f);

	//unbind everything for update loop
	glBindVertexArray(0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	float r = 1.0f;
	float g = 0.0f;
	float b = 0.0f;
	float increment = 0.01f;

	//main render loop
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//bind shader and set color
		glUseProgram(shader);
		glUniform4f(location, r, g, b, 1.0f);

		va.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	//delete shader program
	glDeleteProgram(shader);

	glfwTerminate();
	return 0;
}