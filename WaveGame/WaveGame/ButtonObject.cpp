#include "ButtonObject.h"

ButtonObject::ButtonObject(ButtonType type, Point middle, Sprite normal, Sprite hovered, float width, float height) :
	hovered(hovered), type(type), BaseObject(middle, normal, width, height)
{
}

Sprite& ButtonObject::getSprite()
{
	if (isHovered)
	{
		return hovered;
	}
	return s;
}