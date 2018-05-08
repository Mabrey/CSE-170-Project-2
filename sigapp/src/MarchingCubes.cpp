#include "MarchingCubes.h"
template <typename T>
using ThreeD = std::vector<std::vector<std::vector<T>>>;


MarchingCubes::MarchingCubes()
{
}


MarchingCubes::~MarchingCubes()
{
}

ThreeD<GsVec> MarchingCubes::generateGrid(int resolution)
{
	int canvasSize = 10;
	GsVec point;
	ThreeD<GsPnt> grid(resolution, vector<vector<GsVec>>(resolution, vector<GsVec>(resolution)));
	for(int i = 0; i < resolution; i++)
		for(int j = 0; j < resolution; j++)
			for (int k = 0; k < resolution; k++)
			{
				GsPnt newPoint = GsPnt(-(canvasSize / 2) + ((i * canvasSize) / resolution), -(canvasSize / 2) + ((j * canvasSize) / resolution), -(canvasSize / 2) + ((k * canvasSize) / resolution));
				grid[i][j][k].set(newPoint);
			}

	return grid;
}



ThreeD<Cube> MarchingCubes::generateCubes(ThreeD<GsVec> gridPoints, int resolution)
{
	int canvasSize = 10;
	ThreeD<Cube> gridCube(resolution - 1, vector<vector<Cube>>(resolution - 1, vector<Cube>(resolution - 1)));
	for (int i = 0; i < resolution - 1; i++)
		for (int j = 0; j < resolution - 1; j++)
			for (int k = 0; k < resolution - 1; k++)
			{
				vector<Corner> corners(8);
				
				//back bottom left
				Corner temp = Corner(gridPoints[i][j][k].x, gridPoints[i][j][k].y, gridPoints[i][j][k].z);
				corners.at(0) = temp;

				//front bottom left
				temp = Corner(gridPoints[i][j][k + 1].x, gridPoints[i][j][k + 1].y, gridPoints[i][j][k + 1].z);
				corners.at(1) = temp;

				//back upper left
				temp = Corner(gridPoints[i][j+1][k].x, gridPoints[i][j+1][k].y, gridPoints[i][j+1][k].z);
				corners.at(2) = temp;

				//front upper left
				temp = Corner(gridPoints[i][j + 1][k+1].x, gridPoints[i][j + 1][k+1].y, gridPoints[i][j + 1][k+1].z);
				corners.at(3) = temp;

				//back bottom right
				temp = Corner(gridPoints[i+1][j][k].x, gridPoints[i + 1][j][k].y, gridPoints[i + 1][j][k].z);
				corners.at(4) = temp;

				//front bottom right
				temp = Corner(gridPoints[i + 1][j][k + 1].x, gridPoints[i + 1][j][k + 1].y, gridPoints[i + 1][j][k + 1].z);
				corners.at(5) = temp;

				//back upper right
				temp = Corner(gridPoints[i + 1][j + 1][k].x, gridPoints[i + 1][j + 1][k].y, gridPoints[i + 1][j + 1][k].z);
				corners.at(6) = temp;

				//front upper right
				temp = Corner(gridPoints[i + 1][j + 1][k + 1].x, gridPoints[i + 1][j + 1][k + 1].y, gridPoints[i + 1][j + 1][k + 1].z);
				corners.at(7) = temp;


				Cube newCube = Cube(gridPoints[i][j][k].x + (i * canvasSize) / (resolution * 2), gridPoints[i][j][k].y + (j * canvasSize) / (resolution * 2), gridPoints[i][j][k].z + (k * canvasSize) / (resolution * 2), corners);
			}
	
	return ThreeD<Cube>();
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

Cube::Cube(float x, float y, float z, vector<Corner> newCorners)
{
	center = GsPnt(x, y, z);
	corners = newCorners;
}


Corner::Corner() 
{

	point = GsVec(0, 0, 0);
}

Corner::Corner(float x, float y, float z)
{
	point = GsVec(x, y, z);
}