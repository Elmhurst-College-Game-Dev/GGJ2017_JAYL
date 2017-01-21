#ifndef __POINT_CPP__
#define __POINT_CPP__

#include "Point.h"
#include <cmath>

Point::Point(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Point::getDistance(const Point p) const
{
	return sqrt(pow(p.x - x, 2) - pow(p.y - y, 2));
}

bool Point::operator==(const Point & rhs)
{
	return x==rhs.x && y==rhs.y;
}

#endif