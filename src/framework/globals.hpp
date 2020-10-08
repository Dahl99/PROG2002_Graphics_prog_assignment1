#pragma once
#include <string>
#include <glm/glm.hpp>
#include <vector>
namespace framework {

	const std::string LEVELPATH0 = "../res/levels/level0";

	const std::string PACMANPICTUREPATH = "..res/assets/pacman.png";

	const std::string VERTSHADERPATH = "../res/shaders/shader.vert";
	const std::string FRAGSHADERPATH = "../res/shaders/shader.frag";

	const int WINDOWSIZEX = 28*20, WINDOWSIZEY = 36*20;
	


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

	struct ShaderVertData {
		std::vector<framework::Vertex> wallVertices;
		std::vector<framework::Vertex> collectibleVertices;
	};
}