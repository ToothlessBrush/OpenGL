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
	void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void bind() const;
	void unbind() const;
};