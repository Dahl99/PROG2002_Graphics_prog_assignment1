#pragma once
#include <string>
#include <vector>
#include "globals.hpp"

namespace framework{

	class Map {
	private:
		int sizeX, sizeY, sizeArray;
		int numWalls, numCollecs;
		std::vector<int> array;
		framework::Tile* map;
		EntityPosData entityData;

	public:
		Map(const std::string& levelPath);
		~Map();

		void CreateMap();
		void PrintMap() const;

		ShaderVertData retMapVertices();
		std::vector<GLuint> retMapIndices(int iterations);

		inline std::vector<int> GetArray() const { return array; }
		inline framework::Tile* GetMap() const { return map; }
		inline int GetNumWalls() const{ return numWalls; }
		inline int GetNumCollecs() const{ return numCollecs; }
		inline int GetSizeX() const{ return sizeX; }
		inline int GetSizeY() const{ return sizeY; }
		inline framework::EntityPosData GetPGPos() const { return entityData; }

	};

}