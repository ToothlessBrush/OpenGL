#include "Renderer.h"

void GLAPIENTRY
MessageCallback(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam
) {
	std::cout << "GL CALLBACK: " << (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : "") <<
		"type: " << type << ", severity: " << severity << ", message: " << message << std::endl;

	// Print the file and line number
	if (severity == GL_DEBUG_SEVERITY_HIGH || severity == GL_DEBUG_SEVERITY_MEDIUM) {
		std::cout << __FILE__ << ":" << __LINE__ << std::endl;
		__debugbreak();
	}
}