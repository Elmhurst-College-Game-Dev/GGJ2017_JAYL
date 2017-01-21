#include "BaseObject.h"
#include "Sprite.h"

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