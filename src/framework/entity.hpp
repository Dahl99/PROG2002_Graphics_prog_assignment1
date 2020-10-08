#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

#include "vao.hpp"
#include "vbo.hpp"
#include "ibo.hpp"
#include "shader.hpp"

namespace framework {
	class Entity 
	{
	private:
		glm::vec3 pos, col;
		GLfloat mvSpeed;
		GLboolean isVulnerable;

		std::unique_ptr<VertexArray> vao;
		std::unique_ptr<VertexBuffer> vbo;
		std::unique_ptr<IndexBuffer> ibo;
	
	public:
		Entity(glm::vec3 pos, std::vector<Vertex>& vertices, std::vector<GLuint>& indices);

		void UpdateSprite();
		void Draw(const Shader& shader) const; // Draws pacman onto screen
		void UpdatePos();
		inline glm::vec3 GetPos() const { return pos; };
	};

}