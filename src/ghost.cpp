#include "ghost.hpp"

Ghost::Ghost(glm::vec3 pos, std::vector<framework::Vertex>& vertices, std::vector<GLuint>& indices)
	: Entity(pos, vertices, indices)
{
}

void Ghost::UpdateSprite(framework::Shader& shader, const GLint& dir)
{
}
