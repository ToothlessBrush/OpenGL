#pragma once
class IndexBuffer {
private:
	unsigned int m_RendererID;
	unsigned int m_Count;
public:

	/**
	 * constuctor generates, binds, and inputs data to buffer array.
	 *
	 * \param data
	 * \param size amount of data to be inputed
	 */
	IndexBuffer(const unsigned int* data, unsigned int count);

	/**
	 * deconstructor.
	 *
	 */
	~IndexBuffer();

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

	inline unsigned int getCount() const { return m_Count; }
};
