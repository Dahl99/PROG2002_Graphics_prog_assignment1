#include "pacman.hpp"

Pacman::Pacman(glm::vec3 pos, std::vector<framework::Vertex>& vertices, std::vector<GLuint>& indices) : Entity(pos, vertices, indices)
{
	animTimer = 0.0f;
	animReverse = GL_FALSE;
}

void Pacman::UpdateSprite(framework::Shader& shader, const GLint& dir)
{
	shader.Bind();
	GLfloat texPos[2];

	switch (dir)
	{
	case 0:
		if (animTimer <= 1.0f)
		{
			texPos[0] = 0.0f;
			texPos[1] = 1.0f / 2.0f;
		}
		else if (animTimer <= 2.0f)
		{
			texPos[0] = 1.0 / 6.0f;
			texPos[1] = 1.0f / 2.0f;
		}
		else if (animTimer <= 3.0f)
		{
			texPos[0] = 1.0 / 3.0f;
			texPos[1] = 1.0f / 2.0f;
		}
		else if (animTimer <= 4.0f)
		{
			texPos[0] = 1.0 / 2.0f;
			texPos[1] = 1.0f / 2.0f;
		}
		else
			animTimer = 0.0f;
		break;
		break;
	case 1:
		if (animTimer <= 1.0f)
		{
			texPos[0] = 0.0f;
			texPos[1] = 0.0f;
		}
		else if (animTimer <= 2.0f)
		{
			texPos[0] = 1.0 / 6.0f;
			texPos[1] = 0.0f;
		}
		else if (animTimer <= 3.0f)
		{
			texPos[0] = 1.0 / 3.0f;
			texPos[1] = 0.0f;
		}
		else if (animTimer <= 4.0f)
		{
			texPos[0] = 1.0 / 2.0f;
			texPos[1] = 0.0f;
		}
		else
			animTimer = 0.0f;
		break;
	case 2:
		if (animTimer <= 1.0f)
		{
			texPos[0] = 0.0f;
			texPos[1] = 3.0f / 4.0f;
		}
		else if (animTimer <= 2.0f)
		{
			texPos[0] = 1.0 / 6.0f;
			texPos[1] = 3.0f / 4.0f;
		}
		else if (animTimer <= 3.0f)
		{
			texPos[0] = 1.0 / 3.0f;
			texPos[1] = 3.0f / 4.0f;
		}
		else if (animTimer <= 4.0f)
		{
			texPos[0] = 1.0 / 2.0f;
			texPos[1] = 3.0f / 4.0f;
		}
		else
			animTimer = 0.0f;
		break;
		break;
	case 3:
		if (animTimer <= 1.0f)
		{
			texPos[0] = 0.0f;
			texPos[1] = 1.0f / 4.0f;
		}
		else if (animTimer <= 2.0f)
		{
			texPos[0] = 1.0 / 6.0f;
			texPos[1] = 1.0f / 4.0f;
		}
		else if (animTimer <= 3.0f)
		{
			texPos[0] = 1.0 / 3.0f;
			texPos[1] = 1.0f / 4.0f;
		}
		else if (animTimer <= 4.0f)
		{
			texPos[0] = 1.0 / 2.0f;
			texPos[1] = 1.0f / 4.0f;
		}
		else
			animTimer = 0.0f;
		break;
	default:
		break;
	}

	animTimer += 0.1f;
	shader.SetUniform2fv("posTex", texPos);
}
