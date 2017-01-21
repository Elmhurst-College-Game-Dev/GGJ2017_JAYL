#pragma once
#include "Point.h"
#include "World.h"

extern World* world;

class BaseObject
{
public:
	BaseObject(Point middle, Sprite* s, float width, float height);
	virtual void think() = 0;
	Point getMiddle();
	float getAngle() const { return angle; }
protected:
	Point middle;
	Sprite* s;
	float width;
	float height;
	float angle;
};

