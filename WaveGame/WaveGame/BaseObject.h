#ifndef _BASEOBJ_INCLUDED
#define _BASEOBJ_INCLUDED

#include "Point.h"
#include "World.h"
#include "Sprite.h"

class BaseObject
{
public:
	BaseObject() = default;
	BaseObject(Point middle, Sprite s, float width, float height);
	virtual void think() {} ;
	Point getMiddle();
	void setMiddle(Point p);
	float getAngle() const;
	void rotate(float angle) { this->angle += angle;  }
	float getWidth() const;
	float getHeight() const;
	virtual Sprite &getSprite();
	virtual void draw();
protected:
	Point middle;
	Sprite s;
	float width;
	float height;
	float angle;
};

#endif