#pragma once

#include "BaseObject.h"
#include "BaseEnemy.h"
#include "World.h"

class BaseTurret : public BaseObject
{
public:
	BaseTurret(Point middle, Sprite* s, float width, float height, int damage, unsigned int firerate);
	virtual void think() override;
protected:
	void Shoot(BaseEnemy * enemy);
	inline bool CanFire();

	unsigned long long frameCanFire;
	unsigned int damage;
	unsigned int firerate;
};