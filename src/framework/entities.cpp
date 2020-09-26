#include "entities.hpp"
namespace framework {
	Entity::Entity(glm::vec3 position)
	{
		pos.x = position.x;
		pos.y = position.y;
		pos.z = position.z;

		col.x = 0.0f;
		col.y = 1.0f;
		col.z = 1.0f;

		mvSpeed = 0.f;

		isVulnerable = 1;
		tex = nullptr;
	}
	Entity::Entity(glm::vec3 position, glm::vec3 colour, float speed, bool vulnerable, void* texture)
	{
	}
	void Entity::Draw()
	{
	}
	void Entity::UpdatePos()
	{
	}
	glm::vec3 Entity::GetPos()
	{
		return glm::vec3();
	}
}