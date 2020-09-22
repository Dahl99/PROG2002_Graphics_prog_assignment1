#include <fstream>
#include <iostream>
#include "tilemap.hpp"

namespace framework {
	Map::Map(const std::string& levelPath)
	{
		std::ifstream stream(levelPath);		
		if (stream) {

			stream >> sizeX >> sizeY;


			sizeArray = sizeX * sizeY;
			//array = new int[sizeArray];

			for (int i = 0; i < sizeArray; i++)
			{
				//stream >> array[i];
			}

		}
		else std::cout << "Failed to read map!";

		stream.close();
	}
	Map::~Map()
	{
		//if (array)
			//delete[] array;
	}
	void Map::PrintMap()
	{
		for (int i = 0; i < sizeArray; i++)
		{
			for (i; i % sizeX != 0 && i != 0; i++) 
			{
				std::cout << array[i] << " ";
			}
			std::cout << std::endl;
		}
	}
}