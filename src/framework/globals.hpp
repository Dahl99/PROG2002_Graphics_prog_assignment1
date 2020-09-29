#pragma once
#include <string>
#include <glm/glm.hpp>
namespace framework {

	const std::string LEVELPATH0 = "../res/levels/level0";

	const std::string VERTSHADERPATH = "../res/shaders/shader.vert";
	const std::string FRAGSHADERPATH = "../res/shaders/shader.frag";

	const int WINDOWSIZEX = 800, WINDOWSIZEY = 600;
	


//-------------------------------------------------------------------------------------
//									Tile Structs
//-------------------------------------------------------------------------------------

	struct Vertex {
		glm::vec2 pos, tex;
		glm::vec3 col;

	};

	struct Tile {
		Vertex botLeft, botRight, topLeft, topRight;
	};
}