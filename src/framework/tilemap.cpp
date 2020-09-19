#include <fstream>
#include <iostream>
#include "tilemap.hpp"

namespace framework {
	Map::Map(std::string levelPath)
	{
		std::ifstream map(levelPath);		
		
		map >> sizeX >> sizeY;

		array = new int[(sizeX*sizeY)];

		for (int i = 0; i < sizeX * sizeY; i++)
		{
			map >> array[i];
		}

		map.close();
	}
	Map::~Map()
	{
		delete[] array;
	}
	void Map::PrintMap()
	{
		for (int i = 0; i < sizeX * sizeY; i++)
		{
			for (i; i % sizeX != 0 && i != 0; i++) 
			{
				std::cout << array[i] << " ";
			}
			std::cout << std::endl;
		}
	}
}