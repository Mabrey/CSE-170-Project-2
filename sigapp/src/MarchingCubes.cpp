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
	float canvasSize = 10;
	GsVec point;
	ThreeD<GsPnt> grid = ThreeD<GsPnt>(resolution + 1, vector<vector<GsVec>>(resolution + 1, vector<GsVec>(resolution + 1)));
	
 	for(int i = 0; i <= resolution; i++)
		for(int j = 0; j <= resolution; j++)
			for (int k = 0; k <= resolution; k++)
			{
				GsPnt newPoint = GsPnt(-(canvasSize / 2) + ((i * canvasSize) / resolution),
					-(canvasSize / 2) + ((j * canvasSize) / resolution),
					-(canvasSize / 2) + ((k * canvasSize) / resolution));

				grid[i][j][k].set(newPoint);
				gsout << "points "<< i << " " << j << " " << k << ": "  << newPoint << "\n";
			}

	return grid;
}



ThreeD<Cube> MarchingCubes::generateCubes(ThreeD<GsVec> gridPoints, int resolution)
{
	int canvasSize = 10;
	ThreeD<Cube> gridCube = ThreeD<Cube>(resolution, vector<vector<Cube>>(resolution, vector<Cube>(resolution)));
	for (int i = 0; i < resolution; i++)
		for (int j = 0; j < resolution; j++)
			for (int k = 0; k < resolution; k++)
			{
				vector<Points> Pointss(8);
				
				//back bottom left
				Points temp = Points(gridPoints[i][j][k].x, gridPoints[i][j][k].y, gridPoints[i][j][k].z);
				Pointss[0] = temp;

				//front bottom left
				temp = Points(gridPoints[i][j][k + 1].x, gridPoints[i][j][k + 1].y, gridPoints[i][j][k + 1].z);
				Pointss[1] = temp;

				//back upper left
				temp = Points(gridPoints[i][j+1][k].x, gridPoints[i][j+1][k].y, gridPoints[i][j+1][k].z);
				Pointss[3] = temp;

				//front upper left
				temp = Points(gridPoints[i][j + 1][k+1].x, gridPoints[i][j + 1][k+1].y, gridPoints[i][j + 1][k+1].z);
				Pointss[2] = temp;

				//back bottom right
				temp = Points(gridPoints[i+1][j][k].x, gridPoints[i + 1][j][k].y, gridPoints[i + 1][j][k].z);
				Pointss[4] = temp;

				//front bottom right
				temp = Points(gridPoints[i + 1][j][k + 1].x, gridPoints[i + 1][j][k + 1].y, gridPoints[i + 1][j][k + 1].z);
				Pointss[5] = temp;

				//back upper right
				temp = Points(gridPoints[i + 1][j + 1][k].x, gridPoints[i + 1][j + 1][k].y, gridPoints[i + 1][j + 1][k].z);
				Pointss[7] = temp;

				//front upper right
				temp = Points(gridPoints[i + 1][j + 1][k + 1].x, gridPoints[i + 1][j + 1][k + 1].y, gridPoints[i + 1][j + 1][k + 1].z);
				Pointss[6] = temp;


				Cube newCube = Cube(gridPoints[i][j][k].x + (canvasSize / ((float) resolution * 2)), gridPoints[i][j][k].y + (canvasSize / ((float)resolution * 2)), gridPoints[i][j][k].z + (canvasSize / ((float)resolution * 2)), Pointss);
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