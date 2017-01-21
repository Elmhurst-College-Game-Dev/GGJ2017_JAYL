#ifndef __BASE_TURRET_CPP__
#define __BASE_TURRET_CPP__

#include "BaseTurret.h"

extern World* world;

BaseTurret::BaseTurret(Point middle, Sprite s, float width, float height, int damage, unsigned int firerate, float range, unsigned int cost) :
	BaseObject(middle, s, width, height)
{
	this->damage = damage;
	this->firerate = firerate;
	this->range = range;
}

void BaseTurret::shoot(BaseEnemy * enemy)
{
	enemy->takeDamage(damage);
	frameCanFire = world->getFrameCount() + firerate;
	// TODO: Create sprite for shooting animation
	//CreateFireSprite();
}

bool BaseTurret::canFire() const
{
	return frameCanFire <= world->getFrameCount();
}

bool BaseTurret::isEntInRange(BaseEnemy * enemy)
{
	return middle.getDistance(enemy->getMiddle()) <= range;
}

void BaseTurret::upgrade()
{
	this->s = s;
	this->damage = damage;
	level++;
	upgradePrice += 0; // TODO: How much to increment.
}

int BaseTurret::getLevel()
{
	return level;
}

unsigned int BaseTurret::getUpgradePrice()
{
	return upgradePrice;
}

#endif