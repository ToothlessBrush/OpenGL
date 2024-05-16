#include "IndexBuffer.h"
#include "Renderer.h"
#include <assert.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: m_Count(count)
{
	assert(sizeof(unsigned int) == sizeof(GLuint));

	glGenBuffers(1, &m_RendererID);
	//bind buffer to array buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	//copy data to buffer to be used by GPU, GL_STATIC_DRAW is used for data that is not going to change
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
