#ifndef __STRAIGHT_TURRET__
#define __STRAIGHT_TURRET__


#include "StraightTurret.h"

extern World *world;

StraightTurret::StraightTurret(Point middle, float width, float height, int damage, unsigned int firerate, float range, unsigned int price, const list<string> &sprites)
	: BaseTurret(middle, width, height, damage, firerate, range, price, sprites)
{
}

void StraightTurret::think()
{
	if (canFire())
	{
		auto enemies = world->getEnemies();
		float min = 0;
		BaseEnemy * minEnt = nullptr;
		for (auto ent = enemies->cbegin(); ent != enemies->cend(); ent++)
		{
			if (isEntInRange(*ent))
			{
				float dist = middle.getDistance((*ent)->getMiddle());
				if (min > dist || minEnt == nullptr)
				{
					minEnt = (*ent);
					min = dist;
				}
			}
		}
		if (minEnt != nullptr)
		{
			shoot(minEnt);
		}
	}
}


#endif