#pragma once
class Point
{
public:
	Point(float x, float y);
	Point() = default;
	inline float GetDistance(const Point p);
	float x;
	float y;
};

