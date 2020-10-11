#include <random>

#include "framework/entity.hpp"

class Ghost : public framework::Entity
{
private:
	GLfloat animTimer;
	int dir;

public:
	Ghost(glm::vec3 pos, std::vector<framework::Vertex>& vertices, std::vector<GLuint>& indices);

	void UpdateSprite(framework::Shader& shader, const framework::Direction& dir);
	void Behaviour(std::vector<int> &map, int sizeX, GLfloat &dt, framework::Shader& shader);
	bool CollisionCheck(const glm::vec3& pacmanPos);
};