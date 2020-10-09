#include "entity.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace framework 
{
	Entity::Entity(glm::vec3 pos, std::vector<Vertex>& vertices, std::vector<GLuint>& indices) 
		: pos(pos), col(glm::vec3(1.0f)), mvSpeed(5.0f), isVulnerable(GL_TRUE)
	{
		// Setting start position
		/*this->pos.x = pos.x;
		this->pos.y = pos.y;
		this->pos.z = pos.z;*/

		vao = std::make_unique<VertexArray>();			// Initializing vao
		vbo = std::make_unique<VertexBuffer>(vertices); // Initializing vbo
		ibo = std::make_unique<IndexBuffer>(indices);	// Initializing ibo

		framework::VertexBufferLayout vbl;          // Create a vertex buffer layout
		vbl.Push<GLfloat>(2);                       // Adding position floats to layout
		vbl.Push<GLfloat>(3);                       // Adding color floats to layout
		vbl.Push<GLfloat>(2);                       // Adding tex coords floats to layout

		vao->AddBuffer(*vbo, vbl);					// Populating the vertex buffer
	}

	/*void Entity::UpdateSprite(float texCoords[8])
	{
		vbo->Bind();

		for (int i = 0, j = 0; i < 4; i++, j+=2)
		{
			float temp[2] = { texCoords[j], texCoords[j+1] };
			glBufferSubData(GL_ARRAY_BUFFER, (5*sizeof(float)) * (i+1), 2 * sizeof(float), temp);
		}

		
		float animTimer = 0;
		animTimer += 0.9f;
		if (animTimer > 4.0f)
			animTimer = 0.0f;

		if (animTimer <= 1.0f)
		{
			float temp[8] = { 0.0f, 0.0f,
							  1.0f / 6.0f, 0.0f,
							  1.0f / 6.0f, 1.0f / 4.0f,
							  0.0f, 1.0f / 4.0f };
			pacman.UpdateSprite(temp);
		}
		else if (animTimer <= 2.0f)
		{
			float temp[8] = { 1.0f / 6.0f, 0.0f,
							  1.0f / 3.0f, 0.0f,
							  1.0f / 3.0f, 1.0f / 4.0f,
							  1.0f / 6.0f, 1.0f / 4.0f };
			pacman.UpdateSprite(temp);
		}
		else if (animTimer <= 3.0f)
		{
			float temp[8] = { 1.0f / 3.0f, 0.0f,
							  1.0f / 2.0f, 0.0f,
							  1.0f / 2.0f, 1.0f / 4.0f,
							  1.0f / 3.0f, 1.0f / 4.0f };
			pacman.UpdateSprite(temp);
		}
		else if (animTimer <= 4.0f)
		{
			float temp[8] = { 1.0f / 2.0f, 0.0f,
							  0.6667f, 0.0f,
							  0.6667f, 1.0f / 4.0f,
							  1.0f / 2.0f, 1.0f / 4.0f };
			pacman.UpdateSprite(temp);
		}
	}*/

	void Entity::Draw(Shader& shader) const
	{
		shader.Bind();
		vao->Bind();
		ibo->Bind();

		auto model = glm::translate(glm::mat4(1.f), pos);
		shader.SetUniformMat4f("u_Model", model);

		glDrawElements(GL_TRIANGLES, ibo->GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Entity::UpdatePos(const GLfloat& dt, const GLint& dir)
	{
		switch (dir)
		{
		case 0:
			pos.y += dt * mvSpeed;
			break;
		case 1:
			pos.x += dt * mvSpeed;
			break;
		case 2:
			pos.y -= dt * mvSpeed;
			break;
		case 3:
			pos.x -= dt * mvSpeed;
			break;
		default:
			break;
		}
	}
}