#include "BaseEnemy.h"
#include <assert.h>

extern World* world;

BaseEnemy::BaseEnemy(Point middle, Sprite* s, float width, float height, int health, float speed) :
	BaseObject(middle, s, width, height)
{
	this->health = health;
	this->speed = speed;
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

	float distance = middle.getDistance(goalPoint);
	float x = (middle.x / distance) * speed;
	float y = (middle.y / distance) * speed;

	Point destination = Point(x, y);

	if (middle.getDistance(destination) > distance)
	{
		destination = goalPoint;
	}

	middle = destination;
}

int BaseEnemy::getHealth()
{
	return health;
}