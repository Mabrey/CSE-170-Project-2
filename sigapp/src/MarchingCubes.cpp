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