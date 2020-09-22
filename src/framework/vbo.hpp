#pragma once

#include <GL/glew.h>

namespace framework
{
	// Class containing abstraction of vbo
	class VertexBuffer
	{
	private:
		GLuint rendererID;	//	id for vbo

	public:
		VertexBuffer(const void* data, unsigned int size);	//	Generating, binding and buffering vbo
		~VertexBuffer();									//	Deletes vbo

		void Bind() const;		//	Binds the vbo
		void Unbind() const;	//	Unbinds the vbo
	};
}