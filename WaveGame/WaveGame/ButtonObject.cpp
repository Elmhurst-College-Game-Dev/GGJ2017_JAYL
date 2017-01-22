#include "ButtonObject.h"

ButtonObject::ButtonObject(ButtonType type, Point middle, Sprite normal, Sprite hovered, float width, float height) :
	BaseObject(middle, normal, width, height)
{
	this->type = type;
	this->hovered = hovered;
}

Sprite& ButtonObject::getSprite()
{
	if (isHovered)
	{
		return hovered;
	}
	return s;
}