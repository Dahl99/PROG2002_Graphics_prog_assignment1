#include "framework/entity.hpp"

class Pacman : public framework::Entity
{
private:
	GLfloat animTimer;
	GLboolean animReverse;

public:
	Pacman(glm::vec3 pos, std::vector<framework::Vertex>& vertices, std::vector<GLuint>& indices);

	void UpdateSprite(framework::Shader& shader, const framework::Direction& dir);
};