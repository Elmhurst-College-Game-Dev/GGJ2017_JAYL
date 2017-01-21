#ifndef __AREA_TURRET_CPP__
#define __AREA_TURRET_CPP__

#include "AreaTurret.h"

AreaTurret::AreaTurret(Point middle, Sprite s, float width, float height, int damage, unsigned int firerate, float range, unsigned int cost)
	: BaseTurret(middle, s, width, height, damage, firerate, range, cost)
{
}

void AreaTurret::think()
{
	if (canFire())
	{
		auto enemies = world->getEnemies();
		for (auto ent = enemies->cbegin(); ent != enemies->cend(); ent++)
		{
			if (isEntInRange(*ent))
			{
				shoot(*ent);
			}
		}
	}
}

#endif