#pragma once
#include <string>
namespace framework{

	class Map {
	
	private:
		int sizeX, sizeY;
		int* array;

	public:
		Map(std::string levelPath);
		~Map();
		void PrintMap();

	};

}