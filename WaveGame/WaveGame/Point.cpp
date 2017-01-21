#include "Point.h"
#include <cmath>

Point::Point(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Point::getDistance(const Point p)
{
	return sqrt(pow(p.x - x, 2) - pow(p.y - y, 2));
}