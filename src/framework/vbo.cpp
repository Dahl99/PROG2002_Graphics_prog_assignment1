#include "vbo.hpp"

namespace framework
{
	VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	{
		glGenBuffers(1, &rendererID);								//	Generating the buffer
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);					//	Binding the buffer

		//	Creating and initializing buffer's data store
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &rendererID);							//	Deleting vbo
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, rendererID);					//	Binding vbo
	}

	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);							//	Unbinding vbo
	}
}