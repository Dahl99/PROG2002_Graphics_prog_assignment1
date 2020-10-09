#include "framework/entity.hpp"

class Ghost : public framework::Entity
{
public:
	void UpdateSprite(const GLint& dir);
};