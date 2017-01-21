#include "StraightTurret.h"



StraightTurret::StraightTurret()
{
}


StraightTurret::~StraightTurret()
{
}

void StraightTurret::think()
{
	if (CanFire())
	{
		auto enemies = world->getEnemies();
		float min = 0;
		BaseEnemy * minEnt = nullptr;
		for (auto ent = enemies->cbegin(); ent != enemies->cend(); ent++)
		{
			if (IsEntInRange(*ent))
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
			Shoot(minEnt);
		}
	}
}