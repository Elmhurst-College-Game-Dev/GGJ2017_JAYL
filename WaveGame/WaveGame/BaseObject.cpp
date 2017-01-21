#ifndef __BASE_OBJECT_CPP__
#define __BASE_OBJECT_CPP__

#include "BaseObject.h"
#include "Sprite.h"

extern World* world;

BaseObject::BaseObject(Point mid, Sprite s, float width, float height)
{
	this->middle = mid;
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

float BaseObject::getWidth() const 
{
	return width;
}

float BaseObject::getHeight() const
{
	return height;
}

Sprite &BaseObject::getSprite() {
	return s;
}

#endif