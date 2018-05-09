#include "MarchingCubes.h"
template <typename T>
using ThreeD = std::vector<std::vector<std::vector<T>>>;


MarchingCubes::MarchingCubes()
{
}


MarchingCubes::~MarchingCubes()
{
}

ThreeD<Points> MarchingCubes::generateGrid(int resolution)
{
	float canvasSize = 10;
	GsVec point;
	ThreeD<Points> grid = ThreeD<Points>(resolution + 1, vector<vector<Points>>(resolution + 1, vector<Points>(resolution + 1)));
	
 	for(int i = 0; i <= resolution; i++)
		for(int j = 0; j <= resolution; j++)
			for (int k = 0; k <= resolution; k++)
			{
				GsPnt newPoint = GsPnt(-(canvasSize / 2) + ((i * canvasSize) / resolution),
					-(canvasSize / 2) + ((j * canvasSize) / resolution),
					-(canvasSize / 2) + ((k * canvasSize) / resolution));

				grid[i][j][k].point.set(newPoint);
				grid[i][j][k].value = 0;
				grid[i][j][k].isInside = false;
				
				gsout << "points "<< i << " " << j << " " << k << ": "  << newPoint << "\n";
			}

	return grid;
}



ThreeD<Cube> MarchingCubes::generateCubes(ThreeD<Points> &gridPoints, int resolution)
{
	int canvasSize = 10;
	ThreeD<Cube> gridCube = ThreeD<Cube>(resolution, vector<vector<Cube>>(resolution, vector<Cube>(resolution)));
	for (int i = 0; i < resolution; i++)
		for (int j = 0; j < resolution; j++)
			for (int k = 0; k < resolution; k++)
			{
				vector<Points> corners(8);

				//back bottom left
				Points temp = Points(gridPoints[i][j][k].point.x, gridPoints[i][j][k].point.y, gridPoints[i][j][k].point.z);
				corners[0] = temp;
				*corners[0].cornerVal = gridPoints[i][j][k].value;

				//front bottom left
				temp = Points(gridPoints[i][j][k + 1].point.x, gridPoints[i][j][k + 1].point.y, gridPoints[i][j][k + 1].point.z);
				corners[1] = temp;
				*corners[1].cornerVal = gridPoints[i][j][k + 1].value;

				//back upper left
				temp = Points(gridPoints[i][j + 1][k].point.x, gridPoints[i][j + 1][k].point.y, gridPoints[i][j + 1][k].point.z);
				corners[3] = temp;
				*corners[3].cornerVal = gridPoints[i][j + 1][k].value;

				//front upper left
				temp = Points(gridPoints[i][j + 1][k + 1].point.x, gridPoints[i][j + 1][k + 1].point.y, gridPoints[i][j + 1][k + 1].point.z);
				corners[2] = temp;
				*corners[2].cornerVal = gridPoints[i][j + 1][k + 1].value;

				//back bottom right
				temp = Points(gridPoints[i + 1][j][k].point.x, gridPoints[i + 1][j][k].point.y, gridPoints[i + 1][j][k].point.z);
				corners[4] = temp;
				*corners[4].cornerVal = gridPoints[i + 1][j][k].value;

				//front bottom right
				temp = Points(gridPoints[i + 1][j][k + 1].point.x, gridPoints[i + 1][j][k + 1].point.y, gridPoints[i + 1][j][k + 1].point.z);
				corners[5] = temp;
				*corners[5].cornerVal = gridPoints[i + 1][j][k + 1].value;

				//back upper right
				temp = Points(gridPoints[i + 1][j + 1][k].point.x, gridPoints[i + 1][j + 1][k].point.y, gridPoints[i + 1][j + 1][k].point.z);
				corners[7] = temp;
				*corners[7].cornerVal = gridPoints[i + 1][j + 1][k].value;

				//front upper right
				temp = Points(gridPoints[i + 1][j + 1][k + 1].point.x, gridPoints[i + 1][j + 1][k + 1].point.y, gridPoints[i + 1][j + 1][k + 1].point.z);
				corners[6] = temp;
				*corners[6].cornerVal = gridPoints[i + 1][j + 1][k + 1].value;


				Cube newCube = Cube(gridPoints[i][j][k].point.x + (canvasSize / ((float)resolution * 2)),
					gridPoints[i][j][k].point.y + (canvasSize / ((float)resolution * 2)),
					gridPoints[i][j][k].point.z + (canvasSize / ((float)resolution * 2)), corners);

				gridCube[i][j][k] = newCube;
			}
	
	return gridCube;
}

Cube::Cube()
{
	center = GsPnt(0, 0, 0);
	value = 0;
}

Cube::Cube(float x, float y, float z)
{
	center = GsPnt(x,y,z);
	
}

Cube::Cube(float x, float y, float z, vector<Points> newCorners)
{
	center = GsPnt(x, y, z);
	corners = newCorners;
}

void Cube::findMidpoints() {

	Points temp;
	//midpoint 0
	temp.point.x = (corners[0].point.x + corners[1].point.x) / 2;
	temp.point.y = (corners[0].point.y + corners[1].point.y) / 2;
	temp.point.z = (corners[0].point.z + corners[1].point.z) / 2;
	midpoints.push_back(temp);

	//midpoint 1
	temp.point.x = (corners[1].point.x + corners[2].point.x) / 2;
	temp.point.y = (corners[1].point.y + corners[2].point.y) / 2;
	temp.point.z = (corners[1].point.z + corners[2].point.z) / 2;
	midpoints.push_back(temp);

	//midpoint 2
	temp.point.x = (corners[2].point.x + corners[3].point.x) / 2;
	temp.point.y = (corners[2].point.y + corners[3].point.y) / 2;
	temp.point.z = (corners[2].point.z + corners[3].point.z) / 2;
	midpoints.push_back(temp);

	//midpoint 3
	temp.point.x = (corners[3].point.x + corners[0].point.x) / 2;
	temp.point.y = (corners[3].point.y + corners[0].point.y) / 2;
	temp.point.z = (corners[3].point.z + corners[0].point.z) / 2;
	midpoints.push_back(temp);

	//midpoint 4
	temp.point.x = (corners[4].point.x + corners[5].point.x) / 2;
	temp.point.y = (corners[4].point.y + corners[5].point.y) / 2;
	temp.point.z = (corners[4].point.z + corners[5].point.z) / 2;
	midpoints.push_back(temp);

	//midpoint 5
	temp.point.x = (corners[5].point.x + corners[6].point.x) / 2;
	temp.point.y = (corners[5].point.y + corners[6].point.y) / 2;
	temp.point.z = (corners[5].point.z + corners[6].point.z) / 2;
	midpoints.push_back(temp);

	//midpoint 6
	temp.point.x = (corners[6].point.x + corners[7].point.x) / 2;
	temp.point.y = (corners[6].point.y + corners[7].point.y) / 2;
	temp.point.z = (corners[6].point.z + corners[7].point.z) / 2;
	midpoints.push_back(temp);

	//midpoint 7
	temp.point.x = (corners[7].point.x + corners[4].point.x) / 2;
	temp.point.y = (corners[7].point.y + corners[4].point.y) / 2;
	temp.point.z = (corners[7].point.z + corners[4].point.z) / 2;
	midpoints.push_back(temp);

	//midpoint 8
	temp.point.x = (corners[0].point.x + corners[4].point.x) / 2;
	temp.point.y = (corners[0].point.y + corners[4].point.y) / 2;
	temp.point.z = (corners[0].point.z + corners[4].point.z) / 2;
	midpoints.push_back(temp);

	//midpoint 9
	temp.point.x = (corners[1].point.x + corners[5].point.x) / 2;
	temp.point.y = (corners[1].point.y + corners[5].point.y) / 2;
	temp.point.z = (corners[1].point.z + corners[5].point.z) / 2;
	midpoints.push_back(temp);

	//midpoint 10
	temp.point.x = (corners[3].point.x + corners[7].point.x) / 2;
	temp.point.y = (corners[3].point.y + corners[7].point.y) / 2;
	temp.point.z = (corners[3].point.z + corners[7].point.z) / 2;
	midpoints.push_back(temp);

	//midpoint 11
	temp.point.x = (corners[2].point.x + corners[6].point.x) / 2;
	temp.point.y = (corners[2].point.y + corners[6].point.y) / 2;
	temp.point.z = (corners[2].point.z + corners[6].point.z) / 2;
	midpoints.push_back(temp);
}

void Cube::findConfig() {

	config = 0;
	vector<int> possibleConfigs = { 1, 2, 4, 8, 16, 32, 64, 128 };
	//for each corner in the cube, check if its
	for (int i = 0; i < 8; i++) {
		if (corners[i].isInside)
			config += possibleConfigs[i];
	}
}


Points::Points() 
{
	point = GsVec(0, 0, 0);
	value = 0;
	isInside = false;
}

Points::Points(float x, float y, float z)
{
	point = GsVec(x, y, z);
	value = 0;
	isInside = false;
}