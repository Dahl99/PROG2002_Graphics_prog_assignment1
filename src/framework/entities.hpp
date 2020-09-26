#include <GL/glew.h>
#include <glm/glm.hpp>
namespace framework {
	class Entity {
	private:
		glm::vec3 pos, col;
		GLfloat mvSpeed;
		GLboolean isVulnerable;
		void* tex;
	
	public:
		Entity(glm::vec3 position);
		Entity(glm::vec3 position, glm::vec3 colour, float speed, bool vulnerable, void* texture);
		
		void Draw(); //could eventually get new position in this
		void UpdatePos();
		glm::vec3 GetPos();
	};

}