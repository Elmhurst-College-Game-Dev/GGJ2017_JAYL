#ifndef _POINT_INCLUDED
#define _POINT_INCLUDED

class Point
{
public:
	Point(float x, float y);
	Point() = default;
	inline float getDistance(const Point p);
	float x;
	float y;
	bool operator==(const Point &rhs);
};

#endif