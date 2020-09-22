#pragma once
#include <string>
namespace framework{

	class Map {
	
	private:
		int sizeX, sizeY, sizeArray;
		int* array;

	public:
		Map(const std::string& levelPath);
		~Map();
		void PrintMap();

	};

}