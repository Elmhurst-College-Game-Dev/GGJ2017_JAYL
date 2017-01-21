#include "BaseTurret.h"

BaseTurret::BaseTurret(Point middle, Sprite* s, float width, float height, int damage, unsigned int firerate) :
	BaseObject(middle, s, width, height)
{
	this->damage = damage;
	this->firerate = firerate;
	this->range = range;
}

void BaseTurret::Shoot(BaseEnemy * enemy)
{
	enemy->takeDamage(damage);
	frameCanFire = world->getFrameCount() + firerate;
	// TODO: Create sprite for shooting animation
	CreateFireSprite();
}

bool BaseTurret::CanFire()
{
	return frameCanFire <= world->getFrameCount();
}

bool BaseTurret::IsEntInRange(BaseEnemy * enemy)
{
	return middle.getDistance(enemy->getMiddle()) <= range;
}