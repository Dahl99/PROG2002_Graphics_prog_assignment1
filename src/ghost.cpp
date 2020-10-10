#include "ghost.hpp"

Ghost::Ghost(glm::vec3 pos, std::vector<framework::Vertex>& vertices, std::vector<GLuint>& indices)
	: Entity(pos, vertices, indices)
{
}

void Ghost::UpdateSprite(framework::Shader& shader, const GLint& dir)
{
	GLfloat texPos[2];
	texPos[0] = texPos[1] = 0.0f;
	shader.SetUniform2fv("posTex", texPos);
}
