#ifndef _BASEENEMY_INCLUDED
#define _BASEENEMY_INCLUDED

#include "BaseObject.h"
#include <list>

//using PointItr = std::list<Point>::const_iterator;

class BaseObject;

class BaseEnemy : public BaseObject
{
public:
	BaseEnemy(Point middle, Sprite s, float width, float height, int health, float speed, unsigned int level);
	void takeDamage(int damage);
	virtual void think() override;
	int getHealth();
	unsigned int getLevel();

protected:
	int health;
	float speed;
	int currentPoint;
	unsigned int level;

private:
	void move();
};

#endif