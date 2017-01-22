#ifndef _POINT_INCLUDED
#define _POINT_INCLUDED

class Point
{
public:
	Point(float x, float y);
	explicit Point() ;// = delete;
	Point(const Point& rhs);
	float getDistance(const Point& p) const;
	float x;
	float y;
	bool operator==(const Point &rhs);
	Point operator+(const Point &rhs);
	bool inBox(Point& topLeft, Point& topRight);
};

#endif