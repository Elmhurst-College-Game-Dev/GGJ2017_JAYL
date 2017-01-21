#ifndef _POINT_INCLUDED
#define _POINT_INCLUDED

class Point
{
public:
	Point(float x, float y);
	Point() = default;
	float getDistance(const Point p) const;
	float x;
	float y;
	bool operator==(const Point &rhs);
};

#endif