#include "ghost.hpp"

Ghost::Ghost(glm::vec3 pos, std::vector<framework::Vertex>& vertices, std::vector<GLuint>& indices)
	: Entity(pos, vertices, indices)
{
	animTimer = 0.0f;
}

void Ghost::UpdateSprite(framework::Shader& shader, const framework::Direction& dir)
{
	shader.Bind();
	GLfloat texPos[2];
	switch (dir)
	{
	case framework::Direction::UP:
		if (animTimer <= 1.0f)
		{
			texPos[0] = 0.0f;
			texPos[1] = 1.0f / 2.0f;
		}
		else if (animTimer <= 2.0f)
		{
			texPos[0] = 1.0f / 6.0f;
			texPos[1] = 1.0f / 2.0f;
		}
		else
			animTimer = 0.0f;
		break;
	case framework::Direction::RIGHT:
		if (animTimer <= 1.0f)
		{
			texPos[0] = 0.0f;
			texPos[1] = 0.0f;
		}
		else if (animTimer <= 2.0f)
		{
			texPos[0] = 1.0f / 6.0f;
			texPos[1] = 0.0f;
		}
		else
			animTimer = 0.0f;
		break;
	case framework::Direction::DOWN:
		if (animTimer <= 1.0f)
		{
			texPos[0] = 0.0f;
			texPos[1] = 3.0f / 4.0f;
		}
		else if (animTimer <= 2.0f)
		{
			texPos[0] = 1.0f / 6.0f;
			texPos[1] = 3.0f / 4.0f;
		}
		else
			animTimer = 0.0f;
		break;
	case framework::Direction::LEFT:
		if (animTimer <= 1.0f)
		{
			texPos[0] = 0.0f;
			texPos[1] = 1.0f / 4.0f;
		}
		else if (animTimer <= 2.0f)
		{
			texPos[0] = 1.0f / 6.0f;
			texPos[1] = 1.0f / 4.0f;
		}
		else
			animTimer = 0.0f;
		break;
	default:
		break;
	}

	animTimer += 0.05f;
	shader.SetUniform2fv("posTex", texPos);
}
