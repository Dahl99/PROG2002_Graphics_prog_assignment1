#include <fstream>
#include <iostream>
#include <GL/glew.h>
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
				stream >> array[sizeArray - (i + 1)];
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
		for (int i = 1; i <= sizeArray; i++)
		{
			map[i - 1].botLeft.pos.x = (i-1) % sizeX;
			map[i - 1].botLeft.pos.y = yPos;

			map[i - 1].botRight.pos.x = ((i-1) % sizeX) + 1;
			map[i - 1].botRight.pos.y = yPos;
	
			map[i - 1].topLeft.pos.x = (i-1) % sizeX;
			map[i - 1].topLeft.pos.y = yPos + 1;
			
			map[i - 1].topRight.pos.x = ((i-1) % sizeX) + 1;
			map[i - 1].topRight.pos.y = yPos + 1;

			if (array[i - 1])
			{
				map[i - 1].botLeft.col.y = 0.0f;
				map[i - 1].botLeft.col.x = 0.0f;
				map[i - 1].botLeft.col.z = 0.2f;

				map[i - 1].botRight.col.x = 0.0f;
				map[i - 1].botRight.col.y = 0.0f;
				map[i - 1].botRight.col.z = 0.2f;
		
				map[i - 1].topLeft.col.x = 0.0f;
				map[i - 1].topLeft.col.y = 0.0f;
				map[i - 1].topLeft.col.z = 0.2f;

				map[i - 1].topRight.col.x = 0.0f;
				map[i - 1].topRight.col.y = 0.0f;
				map[i - 1].topRight.col.z = 0.2f;
			}
			else
			{
				map[i - 1].botLeft.col.y = 1.0f;
				map[i - 1].botLeft.col.z = 1.0f;
				map[i - 1].botLeft.col.x = 1.0f;

				map[i - 1].botRight.col.x = 1.0f;
				map[i - 1].botRight.col.y = 1.0f;
				map[i - 1].botRight.col.z = 1.0f;

				map[i - 1].topLeft.col.x = 1.0f;
				map[i - 1].topLeft.col.y = 1.0f;
				map[i - 1].topLeft.col.z = 1.0f;

				map[i - 1].topRight.col.x = 1.0f;
				map[i - 1].topRight.col.y = 1.0f;
				map[i - 1].topRight.col.z = 1.0f;
			}

			if (i % sizeX == 0 && i != 0)
				yPos++;
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

	std::vector<framework::Vertex> Map::retMapVertices()
	{
		std::vector<framework::Vertex> vertices;

		for (int i = 0; i < sizeArray; i++)
		{
			vertices.push_back(map[i].botLeft);
			vertices.push_back(map[i].botRight);
			vertices.push_back(map[i].topLeft);
			vertices.push_back(map[i].topRight);
		}

		return vertices;
	}

	std::vector<GLuint> Map::retMapIndices()
	{
		std::vector<GLuint> indices;

		for (GLuint i = 0; i < sizeArray; i++)
		{
			indices.push_back(i * 4);
			indices.push_back((i * 4) + 1);
			indices.push_back((i * 4) + 2);
			indices.push_back((i * 4) + 2);
			indices.push_back((i * 4) + 3);
			indices.push_back((i * 4) + 1);
		}
		return indices;
	}
}