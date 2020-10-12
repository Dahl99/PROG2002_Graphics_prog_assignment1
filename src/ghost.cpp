#include "ghost.hpp"

Ghost::Ghost(glm::vec3 pos, std::vector<framework::Vertex>& vertices, std::vector<GLuint>& indices)
	: Entity(pos, vertices, indices)
{
	animTimer = 0.0f;
	dir = 0;
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
		{
			animTimer = 0.0f;
			texPos[0] = 1.0f / 6.0f;
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
		else
		{
			animTimer = 0.0f;
			texPos[0] = 1.0f / 6.0f;
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
		else
		{
			animTimer = 0.0f;
			texPos[0] = 1.0f / 6.0f;
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
		else
		{
			animTimer = 0.0f;
			texPos[0] = 1.0f / 6.0f;
			texPos[1] = 1.0f / 4.0f;
		}
		break;
	default:
		break;
	}

	animTimer += 0.05f;
	shader.SetUniform2fv("posTex", texPos);
}

// Ghost movement function
void Ghost::Behaviour(std::vector<int> & map, int sizeX, GLfloat & dt, framework::Shader & shader)
{
	switch (dir) {
	case 0:
		if (map[(int)(((int)(GetPos().y + 1) * sizeX) + (int)(GetPos().x + 0.5))] != 1)
		{
			UpdatePos(dt, framework::Direction(dir));
			UpdateSprite(shader, framework::Direction::UP);
		}
		else // Change dir
		{
			if (rand() % 2)
				dir += 1;
			else dir = 3;
		}
		break;
	case 1:
		if (map[(int)(((int)(GetPos().y + 0.5) * sizeX) + (int)(GetPos().x + 1))] != 1)
		{
			UpdatePos(dt, framework::Direction(dir));
			UpdateSprite(shader, framework::Direction::RIGHT);
		}
		else // Change dir
		{
			if (rand() % 2)
				dir += 1;
			else dir -= 1;
		}
		break;
	case 2:
		if (map[(int)(((int)(GetPos().y) * sizeX) + (int)(GetPos().x + 0.5))] != 1)
		{
			UpdatePos(dt, framework::Direction(dir));
			UpdateSprite(shader, framework::Direction::DOWN);
		}
		else //change dir
		{
			if (rand() % 2)
				dir += 1;
			else dir -= 1;
		}
		break;
	case 3:
		if (map[(int)(((int)(GetPos().y + 0.5) * sizeX) + (int)(GetPos().x))] != 1)
		{
			UpdatePos(dt, framework::Direction(dir));
			UpdateSprite(shader, framework::Direction::LEFT);
		}
		else //change dir
		{
			if (rand() % 2)
				dir = 0;
			else dir -= 1;
		}
		break;
	default:
		break;
	}

}

bool Ghost::CollisionCheck(const glm::vec3& pacmanPos)
{
	const glm::vec3& pos = GetPos();

	// If pacman and the ghost are on the same tile (adds 0.5 to calculate from the midpoint of the sprites
	if ((int)(pacmanPos.x + 0.5) == (int)(pos.x + 0.5) && (int)(pacmanPos.y + 0.5) == (int)(pos.y + 0.5))
		return true;
	else
		return false;
}
