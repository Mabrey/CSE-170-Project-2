#pragma once
# include <sig/sn_manipulator.h>
# include <sig/sn_primitive.h>
# include <sig/sn_transform.h>

# include <vector>
using namespace std;

class Corner {
public:
	GsPnt point;
	float value;

	Corner();
	Corner(float x, float y, float z);
};

class Cube {
public:
	GsPnt center;
	//float size;
	float value;
	vector<Corner> corners;

	Cube();
	Cube(float x, float y, float z);
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
	ThreeD<GsPnt> gridPoints;
	int resolution;

	ThreeD<GsPnt> generateGrid(int resolution);
	ThreeD<Cube> generateCubes(ThreeD<GsVec> gridPoints, int resolution);

};



