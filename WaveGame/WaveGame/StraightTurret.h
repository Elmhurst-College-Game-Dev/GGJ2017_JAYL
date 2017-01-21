#ifndef _STRAIGHTTURRET_INCLUDED
#define _STRAIGHTTURRET_INCLUDED
#include "BaseTurret.h"
#include "World.h"

class StraightTurret : public BaseTurret
{
public:
	StraightTurret(Point middle, Sprite s, float width, float height, int damage, unsigned int firerate, float range, unsigned int price);
	virtual void think() override;
};

#endif