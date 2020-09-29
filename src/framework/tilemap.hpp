#pragma once
#include <string>
#include "globals.hpp"

namespace framework{

	class Map {
	private:
		int sizeX, sizeY, sizeArray;
		int* array;
		framework::Tile* map;

	public:
		Map(const std::string& levelPath);
		~Map();
		void CreateMap();
		void PrintMap();
		int* GetArray();
		framework::Tile* GetMap();
	};

}