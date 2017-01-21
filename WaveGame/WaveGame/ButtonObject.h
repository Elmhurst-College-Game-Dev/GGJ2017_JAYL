#pragma once
#include "BaseObject.h"

extern World* world;

enum ButtonType
{
	BT_Area = 0,
	BT_SS,
	BT_Upgrade
};

class ButtonObject : public BaseObject
{
public:
	ButtonObject(ButtonType type, Point middle, Sprite normal, Sprite hovered, float width, float height);
	bool isHovered = false;
	virtual Sprite &getSprite() override;
	virtual void think() {}
private:
	ButtonType type;
	Sprite hovered;
};

