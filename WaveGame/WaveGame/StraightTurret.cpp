#include "StraightTurret.h"



StraightTurret::StraightTurret()
{
}


StraightTurret::~StraightTurret()
{
}

void StraightTurret::think()
{
	if (frameCanFire <= world->getCurrentFrame())
	{
		const list<BaseObject *> * enemies = world->getEnemies();

		for (auto ent : enemies)
		{
			if (middle.getDistance(ent->getMiddle()) <= range)
			{
				ent.takeDamage(damage);
			}
		}
		
	}
}