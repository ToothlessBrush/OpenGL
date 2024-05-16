#pragma once
class VertexBuffer {
private:
	unsigned int m_RendererID;
public:

	/**
	 * constuctor generates, binds, and inputs data to buffer array.
	 *
	 * \param data
	 * \param size amount of data to be inputed
	 */
	VertexBuffer(const void* data, unsigned int size);

	/**
	 * deconstructor.
	 *
	 */
	~VertexBuffer();

	/**
	 * binds buffer array to opengl.
	 *
	 */
	void bind() const;

	/**
	 * unbinds buffer array from opengl.
	 *
	 */
	void unbind() const;
};
