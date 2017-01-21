#ifndef _BASETURRET_INCLUDED
#define _BASETURRET_INCLUDED

#include "BaseObject.h"
#include "BaseEnemy.h"
#include "World.h"

extern World* world;

class BaseTurret : public BaseObject
{
public:
	BaseTurret(Point middle, Sprite s, float width, float height, int damage, unsigned int firerate, float range, unsigned int cost);
	virtual void think() = 0;
	virtual void upgrade() = 0;
	int getLevel();
	unsigned int getUpgradePrice();

protected:
	void shoot(BaseEnemy * enemy);
	bool canFire() const;
	bool isEntInRange(BaseEnemy * enemy);

	unsigned int level = 1;
	unsigned long long frameCanFire;
	unsigned int damage;
	unsigned int firerate;
	float range;



	unsigned int upgradePrice;
};

#endif