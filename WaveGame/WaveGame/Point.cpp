#ifndef __POINT_CPP__
#define __POINT_CPP__

#include <iostream>
#include "Point.h"
#include <cmath>
#include <assert.h>

using namespace std;

Point::Point(float x, float y)
{
	this->x = x;
	this->y = y;
}

Point::Point(double x, double y)
{
	this->x = x;
	this->y = y;
}

Point::Point(const Point& p)
{
	x = p.x;
	y = p.y;
}

Point::Point()
{
	x = -1.0;
	y = -1.0;
}

float Point::getDistance(const Point& p) const
{
	return sqrt( (p.x - x)*(p.x-x) + (p.y-x)*(p.y-y));
}

bool Point::operator==(const Point & rhs)
{
	return x==rhs.x && y==rhs.y;
}

Point & Point::operator=(const Point & rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	return *this;
}

Point Point::operator+(const Point &rhs)
{
	return Point(x + rhs.x, y + rhs.y);
}


bool Point::inBox(Point& topLeft, Point& bottomRight)
{
	return topLeft.x < x && topLeft.y < y && bottomRight.x > x && bottomRight.y > y;
}
#endif