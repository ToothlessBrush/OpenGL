#include "VertexArray.h"

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_RendererID);
	Bind();
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	Bind();
	vb.bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), reinterpret_cast<const void*>(static_cast<uintptr_t>(offset)));
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const {
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}
