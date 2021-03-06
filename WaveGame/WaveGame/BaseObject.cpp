#ifndef __BASE_OBJECT_CPP__
#define __BASE_OBJECT_CPP__

#include "BaseObject.h"
#include "Sprite.h"

extern World* world;

BaseObject::BaseObject(Point mid, Sprite s, float width, float height) : s(s), width(width), height(height), middle(mid)
{
}

Point BaseObject::getMiddle()
{
	return middle;
}

void BaseObject::setMiddle(Point p)
{
	middle = p;
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

void BaseObject::draw()
{
	s.draw(angle, width, height, middle.x, middle.y);
}

#endif