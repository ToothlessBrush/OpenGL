#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <filesystem>

//constructor and destructor
Shader::Shader(const std::string& ShaderDirectory)
	: m_FilePath(ShaderDirectory), m_RendererID(0) {
	std::pair<std::string, std::string> shaders = parseShaderFiles(ShaderDirectory);
	m_RendererID = createShader(shaders.first, shaders.second);
}

Shader::~Shader() {
	glDeleteProgram(m_RendererID);
}

//private methods
std::string Shader::readShaderFile(const std::string& filepath) {

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

std::pair<std::string, std::string> Shader::parseShaderFiles(const std::string& directory) {
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

unsigned int Shader::createShader(const std::string& vertexShader, const std::string& fragementShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragementShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& source) {
	std::cout << "Compiling " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader..." << std::endl;
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//do error handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		//get and allocate memory for the error message (cpp moment)
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

//public methods
void Shader::bind() const {
	glUseProgram(m_RendererID);
}

void Shader::unbind() const {
	glUseProgram(0);
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
	glUniform4f(getUniformLocation(name), v0, v1, v2, v3);
}

//set uniform helper
unsigned int Shader::getUniformLocation(const std::string& name) {
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) { //cache uniform location since gpu -> cpu is slow
		return m_UniformLocationCache[name];
	}
	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1) {
		std::cout << "Warning: uniform " << name << " does not exist!" << std::endl;
	}
	else {
		m_UniformLocationCache[name] = location;
	}
	return location;
}
