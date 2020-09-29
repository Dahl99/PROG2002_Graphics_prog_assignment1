#include <fstream>
#include <iostream>
#include "tilemap.hpp"

namespace framework {
	// Gets filepath as parameter and reads the tilemap from file
	Map::Map(const std::string& levelPath)
	{
		std::ifstream stream(levelPath);		
		if (stream) 
		{
			stream >> sizeX >> sizeY;
			sizeArray = sizeX * sizeY;
			array = new int[sizeArray];

			for (int i = 0; i < sizeArray; i++)
			{
				stream >> array[i];
			}
		
			CreateMap();
		}
		else std::cout << "Failed to read map!\n";

		stream.close();

	}

	Map::~Map()
	{
		if (array)
			delete[] array;
		if (map)
			delete[] map;
	}

	void Map::CreateMap()
	{
		map = new framework::Tile[sizeArray];

		int yPos = 0;
		for (int i = 0; i < sizeArray; i++)
		{
			if (i % sizeX == 0 && i != 0)
				yPos++;

			map[i].botLeft.pos.x = i % sizeX;
			map[i].botLeft.pos.y = yPos;
			map[i].botLeft.col.x = 0.0f;
			map[i].botLeft.col.y = 0.0f;
			map[i].botLeft.col.z = 1.0f;
			
			map[i].botRight.pos.x = (i % sizeX) + 1;
			map[i].botRight.pos.y = yPos;
			map[i].botRight.col.x = 0.0f;
			map[i].botRight.col.y = 0.0f;
			map[i].botRight.col.z = 1.0f;
			
			map[i].topLeft.pos.x = i % sizeX;
			map[i].topLeft.pos.y = yPos + 1;
			map[i].topLeft.col.x = 0.0f;
			map[i].topLeft.col.y = 0.0f;
			map[i].topLeft.col.z = 1.0f;
			
			map[i].topRight.pos.x = (i % sizeX) + 1;
			map[i].topRight.pos.y = yPos + 1;
			map[i].topRight.col.x = 0.0f;
			map[i].topRight.col.y = 0.0f;
			map[i].topRight.col.z = 1.0f;

		}
	}

	// Function to print map, used to see if its read correctly
	void Map::PrintMap() const
	{
		for (int i = 0; i < sizeArray; i++)
		{
			if (i % sizeX == 0) 
			{
			std::cout << std::endl;
			}
			std::cout << array[i] << " ";
		}

		std::cout << std::endl;
	}
}