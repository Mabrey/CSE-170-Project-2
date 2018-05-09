#pragma once
# include <sig/sn_manipulator.h>
# include <sig/sn_primitive.h>
# include <sig/sn_transform.h>

# include <vector>
using namespace std;


class Points {
public:
	GsPnt point;
	float value;
	bool isInside;
	float *cornerVal;

	Points();
	Points(float x, float y, float z);
};

class Cube {
public:
	GsPnt center;
	//float size;
	float value;
	int config;
	vector<Points> corners;
	vector<Points> midpoints;

	Cube();
	Cube(float x, float y, float z);
	Cube(float x, float y, float z, vector<Points> newCorners);

	void findMidpoints();
	void findConfig();
};

class MarchingCubes
{
public:
	template <typename T>
	using ThreeD = std::vector<std::vector<std::vector<T>>>;
	MarchingCubes();
	~MarchingCubes();
	ThreeD<Cube> gridCubes;
	ThreeD<Points> gridPoints;
	int resolution;

	ThreeD<Points> generateGrid(int resolution);
	ThreeD<Cube> generateCubes(ThreeD<Points> &gridPoints, int resolution);

};



