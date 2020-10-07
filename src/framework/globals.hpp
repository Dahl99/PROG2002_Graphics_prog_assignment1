#pragma once
#include <string>
#include <glm/glm.hpp>
namespace framework {

	const std::string LEVELPATH0 = "../res/levels/level0";

	const std::string PACMANPICTUREPATH = "../res/assets/pacman.png";

	const std::string TILEVERTSHADERPATH = "../res/shaders/tile.vert";
	const std::string TILEFRAGSHADERPATH = "../res/shaders/tile.frag";

	const std::string CHARVERTGSHADERPATH = "../res/shaders/character.vert";
	const std::string CHARFRAGSHADERPATH = "../res/shaders/character.frag";

	const int WINDOWSIZEX = 28 * 20, WINDOWSIZEY = 36 * 20;
	


//-------------------------------------------------------------------------------------
//									Tile Structs
//-------------------------------------------------------------------------------------

	struct Vertex {
		glm::vec2 pos;
		glm::vec3 col;
		glm::vec2 tex;

	};

	struct Tile {
		Vertex botLeft, botRight, topLeft, topRight;
	};
}