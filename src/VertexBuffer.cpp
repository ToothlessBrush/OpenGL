#include "VertexBuffer.h"
#include "Renderer.h"
#include <assert.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size) {

	glGenBuffers(1, &m_RendererID);
	//bind buffer to array buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	//copy data to buffer to be used by GPU, GL_STATIC_DRAW is used for data that is not going to change
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
