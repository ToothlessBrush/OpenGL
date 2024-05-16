#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "vertexBufferLayout.h"

class VertexArray {
private:
	unsigned int m_RendererID;
public:
	/**
	 * constructor.
	 *
	 */
	VertexArray();
	/**
	 * destructor.
	 *
	 */
	~VertexArray();
	/**
	* adds a buffer to the vertex array.
	*
	*\param vb vertex buffer to be added
	*\ param layout layout of the vertex buffer
	*/
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void Bind() const;
	void Unbind() const;
};