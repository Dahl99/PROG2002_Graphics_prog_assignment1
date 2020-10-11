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
			numWalls = numCollecs = 0;
			stream >> sizeX >> sizeY;
			sizeArray = sizeX * sizeY;
			//array = new int[sizeArray];
			for (int i = 0; i < sizeArray; i++)
			{
				int x;
				stream >> x;
				array.insert(array.begin(), x);
				//stream >> array[sizeArray - (i + 1)];
			}
			CreateMap();
		}
		else std::cout << "Failed to read map!\n";

		stream.close();
	}

	Map::~Map()
	{

		if (map)
			delete[] map;
	}


	// Creates a tile and gives that tile 4 vertices for each 
	//  number in the map that is read in the constructor
	void Map::CreateMap()
	{
		map = new framework::Tile[sizeArray];
		glm::vec3 playerPos;
		std::vector<glm::vec3> ghostPos;

		int yPos = 0;
		int playerLoc = 0;
		// For the the map read in the constructor, check each number and assign possition and colour 
		for (int i = 1; i <= sizeArray; i++)
		{

			switch (array[i - 1])
			{
			case 0:
				map[i - 1].botLeft.pos.x = ((i - 1) % sizeX) + COLLECTIBLESIZE;
				map[i - 1].botLeft.pos.y = (yPos)+COLLECTIBLESIZE;

				map[i - 1].botRight.pos.x = (((i - 1) % sizeX) + 1) - COLLECTIBLESIZE;
				map[i - 1].botRight.pos.y = (yPos)+COLLECTIBLESIZE;

				map[i - 1].topLeft.pos.x = ((i - 1) % sizeX) + COLLECTIBLESIZE;
				map[i - 1].topLeft.pos.y = (yPos + 1) - COLLECTIBLESIZE;

				map[i - 1].topRight.pos.x = (((i - 1) % sizeX) + 1) - COLLECTIBLESIZE;
				map[i - 1].topRight.pos.y = (yPos + 1) - COLLECTIBLESIZE;

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
				break;
			case 1:
				map[i - 1].botLeft.pos.x = (i - 1) % sizeX;
				map[i - 1].botLeft.pos.y = yPos;

				map[i - 1].botRight.pos.x = ((i - 1) % sizeX) + 1;
				map[i - 1].botRight.pos.y = yPos;

				map[i - 1].topLeft.pos.x = (i - 1) % sizeX;
				map[i - 1].topLeft.pos.y = yPos + 1;

				map[i - 1].topRight.pos.x = ((i - 1) % sizeX) + 1;
				map[i - 1].topRight.pos.y = yPos + 1;

				map[i - 1].botLeft.col.y = 0.0f;
				map[i - 1].botLeft.col.x = 0.0f;
				map[i - 1].botLeft.col.z = 0.6f;

				map[i - 1].botRight.col.x = 0.0f;
				map[i - 1].botRight.col.y = 0.0f;
				map[i - 1].botRight.col.z = 0.6f;

				map[i - 1].topLeft.col.x = 0.0f;
				map[i - 1].topLeft.col.y = 0.0f;
				map[i - 1].topLeft.col.z = 0.6f;

				map[i - 1].topRight.col.x = 0.0f;
				map[i - 1].topRight.col.y = 0.0f;
				map[i - 1].topRight.col.z = 0.6f;
				break;
			case 2: // Sets player pos if tile type is 2

				playerPos = glm::vec3((float)(i % sizeX), (float)(yPos), 1.0f);

				map[i - 1].botLeft.pos.x = ((i - 1) % sizeX) + COLLECTIBLESIZE;
				map[i - 1].botLeft.pos.y = (yPos)+COLLECTIBLESIZE;

				map[i - 1].botRight.pos.x = (((i - 1) % sizeX) + 1) - COLLECTIBLESIZE;
				map[i - 1].botRight.pos.y = (yPos)+COLLECTIBLESIZE;

				map[i - 1].topLeft.pos.x = ((i - 1) % sizeX) + COLLECTIBLESIZE;
				map[i - 1].topLeft.pos.y = (yPos + 1) - COLLECTIBLESIZE;

				map[i - 1].topRight.pos.x = (((i - 1) % sizeX) + 1) - COLLECTIBLESIZE;
				map[i - 1].topRight.pos.y = (yPos + 1) - COLLECTIBLESIZE;

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
				break;
			case 3: // Sets ghost position if tile type is 3
				ghostPos.push_back(glm::vec3((float)(i % sizeX)-1, (float)(yPos), 1.0f));
				break;
			default:
				break;
			}
			if (i % sizeX == 0 && i != 0)
				yPos++;
		}

		// Adding vertices and entity positions to entityData
		entityData.vertices.push_back(map[0].botLeft);
		entityData.vertices.push_back(map[0].botRight);
		entityData.vertices.push_back(map[0].topLeft);
		entityData.vertices.push_back(map[0].topRight);

		entityData.positions.push_back(playerPos); // Player pos gets added first

		for (const auto& element : ghostPos)	   // Ghost pos gets added last
			entityData.positions.push_back(element);
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

	// Loops through mapsize and puts the data for each tile into one of two vector containers,
	//  one for walls and one for collectibles
	ShaderVertData Map::retMapVertices()
	{
		ShaderVertData mapVertices;

		for (int i = 0; i < sizeArray; i++)
		{
			if(array[i] && array[i] != 2)
			{
				mapVertices.wallVertices.push_back(map[i].botLeft);
				mapVertices.wallVertices.push_back(map[i].botRight);
				mapVertices.wallVertices.push_back(map[i].topLeft);
				mapVertices.wallVertices.push_back(map[i].topRight);
				numWalls++;
			}
			else
			{
				mapVertices.collectibleVertices.push_back(map[i].botLeft);
				mapVertices.collectibleVertices.push_back(map[i].botRight);
				mapVertices.collectibleVertices.push_back(map[i].topLeft);
				mapVertices.collectibleVertices.push_back(map[i].topRight);
				numCollecs++;
			}
		}

		return mapVertices;
	}


	// Creates the indice arrays for the map
	std::vector<GLuint> Map::retMapIndices(int iterations)
	{
		std::vector<GLuint> indices;

		for (GLuint i = 0; i < iterations; i++)
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