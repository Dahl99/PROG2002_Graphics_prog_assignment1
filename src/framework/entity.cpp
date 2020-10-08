#include "entity.hpp"

namespace framework 
{
	Entity::Entity(glm::vec3 pos, std::vector<Vertex>& vertices, std::vector<GLuint>& indices) 
		: col(glm::vec3(1.0f))
	{
		// Setting start position
		this->pos.x = pos.x;
		this->pos.y = pos.y;
		this->pos.z = pos.z;

		mvSpeed = 0.f;

		isVulnerable = GL_TRUE;

		vao = std::make_unique<VertexArray>();			// Initializing vao
		vbo = std::make_unique<VertexBuffer>(vertices); // Initializing vbo
		ibo = std::make_unique<IndexBuffer>(indices);	// Initializing ibo

		framework::VertexBufferLayout vbl;          // Create a vertex buffer layout
		vbl.Push<GLfloat>(2);                       // Adding position floats to layout
		vbl.Push<GLfloat>(3);                       // Adding color floats to layout
		vbl.Push<GLfloat>(2);                       // Adding tex coords floats to layout

		vao->AddBuffer(*vbo, vbl);					// Populating the vertex buffer
	}
	void Entity::UpdateSprite()
	{
	}
	void Entity::Draw(const Shader& shader) const
	{
		shader.Bind();
		vao->Bind();
		ibo->Bind();

		glDrawElements(GL_TRIANGLES, ibo->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	void Entity::UpdatePos()
	{

	}
}