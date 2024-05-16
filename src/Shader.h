#pragma once
#include <string>
#include <unordered_map>

class Shader {
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache; //cache for uniforms
public:
	Shader(const std::string& ShaderDirectory);
	~Shader();

	/**
	 * bind the shader program.
	 *
	 */
	void bind() const;

	/**
	 * unbind the shader program.
	 *
	 */
	void unbind() const;

	/**
	 * set a uniform with 4 floats.
	 *
	 * \param name name of the uniform
	 * \param v0
	 * \param v1
	 * \param v2
	 * \param v3
	 */
	void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
private:

	/**
	 *reads a file and outputs it as a string.
	 *
	 * \param filepath path to the file
	 * \return string of file contents
	 */
	std::string readShaderFile(const std::string& filepath);

	/**
	 * given the shader directory it reads shader programs returns them both as strings.
	 *
	 * \param directory path to the directory containing the shader files
	 * \return the pair of vertex and fragment shader strings
	 */
	std::pair<std::string, std::string> parseShaderFiles(const std::string& directory);

	/**
	 * compiles and attaches shaders to opengl.
	 *
	 * \param vertexShader
	 * \param fragementShader
	 * \return shader program
	 */
	unsigned int createShader(const std::string& vertexShader, const std::string& fragmentShader);

	/**
	 * compiles opengl shader program and returns a refrence to it.
	 *
	 * \param type type of shader
	 * \param source shader source code
	 * \return refrence to shader
	 */
	unsigned int compileShader(unsigned int type, const std::string& source);

	/**
	 * get the gpu memory location of the uniform.
	 *
	 * \param name
	 * \return
	 */
	unsigned int getUniformLocation(const std::string& name);
};
