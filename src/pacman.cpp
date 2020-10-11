#include "pacman.hpp"

Pacman::Pacman(glm::vec3 pos, std::vector<framework::Vertex>& vertices, std::vector<GLuint>& indices) 
	: Entity(pos, vertices, indices)
{
	animTimer = 0.0f;
	animReverse = GL_FALSE;
}

/*
* Updating sprite by using a unfiform based on direction and an animation timer
* sprite will also be reversed if it's the last sprite in line for smoother animation
*/
void Pacman::UpdateSprite(framework::Shader& shader, const framework::Direction& dir)
{
	shader.Bind();
	GLfloat texPos[2];
	if (!animReverse)
	{
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
			else if (animTimer <= 3.0f)
			{
				texPos[0] = 1.0f / 3.0f;
				texPos[1] = 1.0f / 2.0f;
			}
			else if (animTimer <= 4.0f)
			{
				texPos[0] = 1.0f / 2.0f;
				texPos[1] = 1.0f / 2.0f;
			}
			else if (animTimer > 4.0f)
			{
				animReverse = !animReverse;
				animTimer = 4.0f;
				texPos[0] = 1.0f / 2.0f;
				texPos[1] = 1.0f / 2.0f;
			}
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
			else if (animTimer <= 3.0f)
			{
				texPos[0] = 1.0f / 3.0f;
				texPos[1] = 0.0f;
			}
			else if (animTimer <= 4.0f)
			{
				texPos[0] = 1.0f / 2.0f;
				texPos[1] = 0.0f;
			}
			else if (animTimer > 4.0f)
			{
				animReverse = !animReverse;
				animTimer = 4.0f;
				texPos[0] = 1.0f / 2.0f;
				texPos[1] = 0.0f;
			}
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
			else if (animTimer <= 3.0f)
			{
				texPos[0] = 1.0f / 3.0f;
				texPos[1] = 3.0f / 4.0f;
			}
			else if (animTimer <= 4.0f)
			{
				texPos[0] = 1.0f / 2.0f;
				texPos[1] = 3.0f / 4.0f;
			}
			else if (animTimer > 4.0f)
			{
				animReverse = !animReverse;
				animTimer = 4.0f;
				texPos[0] = 1.0f / 2.0f;
				texPos[1] = 3.0f / 4.0f;
			}
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
			else if (animTimer <= 3.0f)
			{
				texPos[0] = 1.0f / 3.0f;
				texPos[1] = 1.0f / 4.0f;
			}
			else if (animTimer <= 4.0f)
			{
				texPos[0] = 1.0f / 2.0f;
				texPos[1] = 1.0f / 4.0f;
			}
			else if (animTimer > 4.0f)
			{
				animReverse = !animReverse;
				animTimer = 4.0f;
				texPos[0] = 1.0f / 2.0f;
				texPos[1] = 1.0f / 4.0f;
			}
			break;
		default:
			break;
		}

		animTimer += 0.3f;
	}
	else
	{
		switch (dir)
		{
		case 0:
			if (animTimer >= 3.0f)
			{
				texPos[0] = 1.0f / 2.0f;
				texPos[1] = 1.0f / 2.0f;
			}
			else if (animTimer >= 2.0f)
			{
				texPos[0] = 1.0f / 3.0f;
				texPos[1] = 1.0f / 2.0f;
			}
			else if (animTimer >= 1.0f)
			{
				texPos[0] = 1.0f / 6.0f;
				texPos[1] = 1.0f / 2.0f;
			}
			else if (animTimer >= 0.0f)
			{
				texPos[0] = 0.0f;
				texPos[1] = 1.0f / 2.0f;
			}
			else if (animTimer < 0.0f)
			{
				animReverse = !animReverse;
				animTimer = 0.0f;
				texPos[0] = 0.0f;
				texPos[1] = 1.0f / 2.0f;
			}
			break;
		case 1:
			if (animTimer >= 3.0f)
			{
				texPos[0] = 1.0f / 2.0f;
				texPos[1] = 0.0f;
			}
			else if (animTimer >= 2.0f)
			{
				texPos[0] = 1.0f / 3.0f;
				texPos[1] = 0.0f;
			}
			else if (animTimer >= 1.0f)
			{
				texPos[0] = 1.0f / 3.0f;
				texPos[1] = 0.0f;
			}
			else if (animTimer >= 0.0f)
			{
				texPos[0] = 0.0f;
				texPos[1] = 0.0f;
			}
			else if(animTimer < 0.0f)
			{
				animReverse = !animReverse;
				animTimer = 0.0f;
				texPos[0] = 0.0f;
				texPos[1] = 0.0f;
			}
			break;
		case 2:
			if (animTimer >= 3.0f)
			{
				texPos[0] = 1.0f / 2.0f;
				texPos[1] = 3.0f / 4.0f;
			}
			else if (animTimer >= 2.0f)
			{
				texPos[0] = 1.0f / 3.0f;
				texPos[1] = 3.0f / 4.0f;
			}
			else if (animTimer >= 1.0f)
			{
				texPos[0] = 1.0f / 6.0f;
				texPos[1] = 3.0f / 4.0f;
			}
			else if (animTimer >= 0.0f)
			{
				texPos[0] = 0.0f;
				texPos[1] = 3.0f / 4.0f;
			}
			else if (animTimer < 0.0f)
			{
				animReverse = !animReverse;
				animTimer = 0.0f;
				texPos[0] = 0.0f;
				texPos[1] = 3.0f / 4.0f;
			}
			break;
		case 3:
			if (animTimer >= 3.0f)
			{
				texPos[0] = 1.0f / 2.0f;
				texPos[1] = 1.0f / 4.0f;
			}
			else if (animTimer >= 2.0f)
			{
				texPos[0] = 1.0f / 3.0f;
				texPos[1] = 1.0f / 4.0f;
			}
			else if (animTimer >= 1.0f)
			{
				texPos[0] = 1.0f / 6.0f;
				texPos[1] = 1.0f / 4.0f;
			}
			else if (animTimer >= 0.0f)
			{
				texPos[0] = 0.0f;
				texPos[1] = 1.0f / 4.0f;
			}
			else if (animTimer < 0.0f)
			{
				animReverse = !animReverse;
				animTimer = 0.0f;
				texPos[0] = 0.0f;
				texPos[1] = 1.0f / 4.0f;
			}
			break;
		default:
			break;
		}

		animTimer -= 0.3f;
	}

	shader.SetUniform2fv("posTex", texPos);
}
