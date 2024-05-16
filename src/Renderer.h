#include <GL/glew.h>

#include <iostream>


/**
 * called by opengl for debug or error, prints the errror and creates breakpoint to trace callstack.
 *
 * \param source
 * \param type
 * \param id
 * \param severity
 * \param length
 * \param message
 * \param userParam
 * \return
 */
void GLAPIENTRY
MessageCallback(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam
);
