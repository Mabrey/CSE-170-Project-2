#pragma once
# include <sig/sn_manipulator.h>
# include <vector>
using namespace std;

class Corner {
public:
	float xCoord;
	float yCoord;
	float zCoord;
	float value;

	Corner(float x, float y, float z);
};

class Cube {
public:
	float xCoord;
	float yCoord;
	float zCoord;
	//float size;
	float value;
	vector<Corner> corners;

	Cube();
	Cube(float x, float y, float z, vector<Corner> newCorners);

};

class MarchingCubes
{
public:
	template <typename T>
	using ThreeD = std::vector<std::vector<std::vector<T>>>;
	MarchingCubes();
	~MarchingCubes();
	ThreeD<Cube> gridCubes;
	ThreeD<float> gridPoints;
	int resolution;

	ThreeD<GsVec> generateGrid(int resolution);
	ThreeD<Cube> generateCubes(ThreeD<GsVec> gridPoints, int resolution);

};



