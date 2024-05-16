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
#include "Shader.h"

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

	//create layout and add buffer to vertex array since vertex array has a layout for the buffer we need to add it to the vertex array a certain way
	VertexBufferLayout layout;
	layout.push<float>(2);
	va.addBuffer(vb, layout);

	//create index buffer and bind while the vao is still bound no need to add a layout since it is an index buffer which doesnt need a layout
	IndexBuffer ib(indices, 6);

	Shader shader("res/shaders");
	shader.bind();

	shader.setUniform4f("u_Color", 0.2f, 0.8f, 1.0f, 1.0f);

	//unbind everything for update loop
	va.unbind();
	vb.unbind();
	ib.unbind();
	shader.unbind();

	float r = 1.0f;
	float g = 0.0f;
	float b = 0.0f;
	float increment = 0.01f;

	//main render loop
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//bind shader and set color
		shader.bind();
		shader.setUniform4f("u_Color", r, g, b, 1.0f);

		//bind vertex array which contains the vertex buffer and index buffer
		va.bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}