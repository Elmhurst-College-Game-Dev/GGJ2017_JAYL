#ifndef __POINT_CPP__
#define __POINT_CPP__

#include <iostream>
#include "Point.h"
#include <cmath>
#include <assert.h>

using namespace std;

Point::Point(float x, float y)
{
	cout << "Called right constructor" << endl;
	this->x = x;
	this->y = y;
}

Point::Point(const Point& p)
{
//	cout << "Called copy" << endl;
	x = p.x;
	y = p.y;
}

Point::Point()
{
	cout << "I wanna die" << endl;
	x = -1.0;
	y = -1.0;
}

float Point::getDistance(const Point& p) const
{
	return sqrt(pow(p.x - x, 2) - pow(p.y - y, 2));
}

bool Point::operator==(const Point & rhs)
{
	return x==rhs.x && y==rhs.y;
}

Point Point::operator+(const Point &rhs)
{
	return Point(x + rhs.x, y + rhs.y);
}


bool Point::inBox(Point& topLeft, Point& bottomRight)
{
	return topLeft.x < x && topLeft.y > y && bottomRight.x > x && bottomRight.y < y;
}
#endif