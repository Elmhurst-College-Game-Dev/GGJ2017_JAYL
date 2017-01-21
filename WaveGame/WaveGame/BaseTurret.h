#ifndef _BASETURRET_INCLUDED
#define _BASETURRET_INCLUDED

#include "BaseObject.h"
#include "BaseEnemy.h"
#include "World.h"

extern World* world;

class BaseTurret : public BaseObject
{
public:
	BaseTurret(Point middle, float width, float height, int damage, unsigned int firerate, float range, unsigned int cost, list<string> sprites);
	virtual void think() = 0;
	virtual void upgrade();
	int getLevel();
	unsigned int getUpgradePrice();

protected:
	void shoot(BaseEnemy * enemy);
	bool canFire() const;
	bool isEntInRange(BaseEnemy * enemy);

	unsigned int level = 1;
	unsigned long long frameCanFire;
	unsigned long long frameLastFire;
	unsigned int damage;
	unsigned int firerate;
	float range;

	list<string> spriteNames;
	list<string>::iterator currentSprite;

	unsigned int upgradePrice;
};

#endif