#ifndef __BASE_OBJECT_CPP__
#define __BASE_OBJECT_CPP__

#include "BaseObject.h"
#include "Sprite.h"

extern World* world;

BaseObject::BaseObject(Point middle, Sprite* s, float width, float height)
{
	this->middle = middle;
	this->s = s;
	this->width = width;
	this->height = height;
}

Point BaseObject::getMiddle()
{
	return middle;
}

float BaseObject::getAngle() const
{
	return angle;
}

#endif