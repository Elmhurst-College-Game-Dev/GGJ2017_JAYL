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