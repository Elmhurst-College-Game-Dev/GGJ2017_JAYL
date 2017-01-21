#ifndef _BASETURRET_INCLUDED
#define _BASETURRET_INCLUDED

#include "BaseObject.h"
#include "BaseEnemy.h"
#include "World.h"

class BaseTurret : public BaseObject
{
public:
	BaseTurret(Point middle, Sprite* s, float width, float height, int damage, unsigned int firerate, float range);
	virtual void think() = 0;

protected:
	void Shoot(BaseEnemy * enemy);
	bool CanFire() const;
	bool IsEntInRange(BaseEnemy * enemy);

	unsigned long long frameCanFire;
	unsigned int damage;
	unsigned int firerate;
	float range;
};

#endif