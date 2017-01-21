#pragma once
#include "Point.h"

extern World* world;

class BaseObject
{
public:
	BaseObject(Point middle, Sprite* s, float width, float height);
	~BaseObject();
	virtual void think() = 0;
	Point getMiddle();

protected:
	Point middle;
	Sprite* s;
	float width;
	float height;
	float angle;
};

