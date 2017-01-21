#pragma once
#include "Point.h"

class BaseObject
{
public:
	BaseObject(Point middle, Sprite* s, float width, float height);
	~BaseObject();
	virtual void think();
protected:
	Point middle;
	Sprite* s;
	float width;
	float height;
	float angle;
};

