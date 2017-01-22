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
	currentPoint = 0;
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
	Point goalPoint(world->getPath()[currentPoint]);
	//cout << "( " << goalPoint.x << ", " << goalPoint.y << " )" << endl;
	float distance = this->middle.getDistance(goalPoint);
	float x = 0.0f;
	float y = 0.0f;
	 x = ( (goalPoint.x-middle.x) / distance) * speed;
	 y = ((goalPoint.y -middle.y) / distance) * speed;
	Point destination(middle.x+x,middle.y+y);
	//Comparing how much you will move with how far away it is
	if (distance < speed)
	{
		cout << "Im alive" << endl;
		if (currentPoint < world->getPath().size()-1) {
			destination = goalPoint;
			currentPoint++;
		}
	}

	this->middle = destination;

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