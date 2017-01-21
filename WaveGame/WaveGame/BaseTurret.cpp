#include "BaseTurret.h"

BaseTurret::BaseTurret(Point middle, Sprite* s, float width, float height, int damage, unsigned int firerate) :
	BaseObject(middle, s, width, height)
{
	this->damage = damage;
	this->firerate = firerate;
}

void BaseTurret::Shoot(BaseEnemy * enemy)
{
	enemy->takeDamage(damage);
	frameCanFire = world->getCurrentFrame() + firerate;
}

bool BaseTurret::CanFire()
{
	return frameCanFire <= world->getCurrentFrame();
}