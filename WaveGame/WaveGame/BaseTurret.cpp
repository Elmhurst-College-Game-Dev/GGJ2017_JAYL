#ifndef __BASE_TURRET_CPP__
#define __BASE_TURRET_CPP__

#include "BaseTurret.h"
#include <assert.h>
#include "RenderControl.h"

extern World* world;
extern RenderControl renderController;

BaseTurret::BaseTurret(Point middle, float width, float height, int damage, unsigned int firerate, float range, unsigned int cost, list<string> sprites) :
	BaseObject(middle, s, width, height)
{
	assert(sprites.size() != 0);
	currentSprite = sprites.begin();
	this->damage = damage;
	this->firerate = firerate;
	this->range = range;
	this->s = renderController.get(*currentSprite);
}

void BaseTurret::shoot(BaseEnemy * enemy)
{
	enemy->takeDamage(damage);
	unsigned long long frameCount = world->getFrameCount();
	frameCanFire = frameCount + firerate;
	// TODO: Create sprite for shooting animation
	if (frameLastFire != frameCount) // Prevents aoe from firing multiple times in a single frame.
	{
		//CreateFireSprite();
	}
	frameLastFire = frameCount;
	
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
	currentSprite++;
	this->s = renderController.get(*currentSprite);
	this->damage += damage; // TODO: How much to increment;
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