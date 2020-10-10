#include "framework/entity.hpp"

class Ghost : public framework::Entity
{
public:
	Ghost(glm::vec3 pos, std::vector<framework::Vertex>& vertices, std::vector<GLuint>& indices);

	void UpdateSprite(framework::Shader& shader, const GLint& dir);
};