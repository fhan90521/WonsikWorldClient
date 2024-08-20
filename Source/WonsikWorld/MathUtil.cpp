#include "MathUtil.h"
#include <utility>
#include <cmath>
float GetDistanceBetweenTwoPoint(float x1, float y1, float x2, float y2)
{
	float xDiff = x1 - x2;
	float yDiff = y1 - y2;
	return sqrt(pow(xDiff, 2) + pow(yDiff, 2));
}

bool IsSameGrid(float x1, float y1, float x2, float y2, float cellSize)
{
	int gridX1 = x1 / cellSize;
	int gridY1 = y1 / cellSize;

	int gridX2 = x2 / cellSize;
	int gridY2 = y2 / cellSize;

	return (gridX1 == gridX2) && (gridY1 == gridY2);
}

void Normalize(std::pair<float, float>& vector)
{
	if (vector.first == 0 && vector.second == 0)
	{
		return;
	}
	float divideVal = sqrt(pow(vector.first, 2) + pow(vector.second, 2));
	vector.first = vector.first / divideVal;
	vector.second = vector.second / divideVal;
}
