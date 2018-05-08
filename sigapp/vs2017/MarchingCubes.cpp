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
	ThreeD<GsVec> grid(resolution, vector<vector<GsVec>>(resolution, vector<GsVec>(resolution)));
	for(int i = 0; i < resolution; i++)
		for(int j = 0; j < resolution; j++)
			for (int k = 0; k < resolution; k++)
			{
				GsVec newPoint = GsVec(-(canvasSize / 2) + ((i * canvasSize) / resolution), -(canvasSize / 2) + ((j * canvasSize) / resolution), -(canvasSize / 2) + ((k * canvasSize) / resolution));
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
				Corner temp = Corner(gridPoints[i][j][k].x, gridPoints[i][j][k].y, gridPoints[i][j][k].z);
				corners.at(0) = temp;

				temp = Corner(gridPoints[i][j][k + 1].x, gridPoints[i][j][k + 1].y, gridPoints[i][j][k + 1].z);
				corners.at(1) = temp;

				temp = Corner(gridPoints[i][j+1][k].x, gridPoints[i][j+1][k].y, gridPoints[i][j+1][k].z);
				corners.at(2) = temp;

				temp = Corner(gridPoints[i][j + 1][k+1].x, gridPoints[i][j + 1][k+1].y, gridPoints[i][j + 1][k+1].z);
				corners.at(3) = temp;

				Corner temp = Corner(gridPoints[i+1][j][k].x, gridPoints[i + 1][j][k].y, gridPoints[i + 1][j][k].z);
				corners.at(4) = temp;

				temp = Corner(gridPoints[i + 1][j][k + 1].x, gridPoints[i + 1][j][k + 1].y, gridPoints[i + 1][j][k + 1].z);
				corners.at(5) = temp;

				temp = Corner(gridPoints[i + 1][j + 1][k].x, gridPoints[i + 1][j + 1][k].y, gridPoints[i + 1][j + 1][k].z);
				corners.at(6) = temp;

				temp = Corner(gridPoints[i + 1][j + 1][k + 1].x, gridPoints[i + 1][j + 1][k + 1].y, gridPoints[i + 1][j + 1][k + 1].z);
				corners.at(7) = temp;


				Cube newCube = Cube(gridPoints[i][j][k].x + (i * canvasSize) / (resolution * 2), gridPoints[i][j][k].y + (j * canvasSize) / (resolution * 2), gridPoints[i][j][k].z + (k * canvasSize) / (resolution * 2), corners);
			}
	
	return ThreeD<Cube>();
}

Cube::Cube()
{
	xCoord = 0;
	yCoord = 0;
	zCoord = 0;
	//size = 0;
	value = 0;
}

Cube::Cube(float x, float y, float z, vector<Corner> newCorners)
{
	xCoord = x;
	yCoord = y;
	zCoord = z;
	//size = width;
	corners = newCorners;
}

Corner::Corner(float x, float y, float z)
{
	xCoord = x;
	yCoord = y;
	zCoord = z;
}
