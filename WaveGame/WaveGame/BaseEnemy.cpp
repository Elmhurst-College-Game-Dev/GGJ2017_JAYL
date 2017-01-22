#ifndef __BASE_ENEMY_CPP__
#define __BASE_ENEMY_CPP__

#include "BaseEnemy.h"
#include <assert.h>

extern World *world;

BaseEnemy::BaseEnemy(Point middle, Sprite s, float width, float height, int health, float speed, unsigned int level) :
	BaseObject(middle, s, width, height)
{
	this->health = health;
	this->speed = speed;
	this->level = level;
	assert(world->getPath() != nullptr);
	nextPoint = world->getPath()->cbegin();
}

void BaseEnemy::takeDamage(int damage)
{
	health -= damage;
}

void BaseEnemy::think()
{
	move();
	if (world->getEndPoint() == middle)
	{
		health = 0;
		world->damagePlayer();
	}
}

void BaseEnemy::move()
{
	const Point goalPoint = *nextPoint;

	float deltaX = goalPoint.x - middle.x;
	float deltaY = goalPoint.y - middle.y;

	float goalDist = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	if (goalDist > speed)
	{
		float ratio = speed / goalDist;
		middle = Point(ratio * deltaX + middle.x, ratio * deltaY + middle.y);
	}
	else
	{
		middle = goalPoint;
	}

}

int BaseEnemy::getHealth()
{
	return health;
}

unsigned int BaseEnemy::getLevel()
{
	return level;
}

#endif