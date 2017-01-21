#ifndef _BASEOBJ_INCLUDED
#define _BASEOBJ_INCLUDED

#include "Point.h"
#include "World.h"
#include "Sprite.h"

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

#endif