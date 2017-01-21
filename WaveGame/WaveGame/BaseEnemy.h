#pragma once
#include "BaseObject.h"
#include <list>

using PointItr = std::list<Point>::const_iterator;

class BaseEnemy : public BaseObject
{
public:
	BaseEnemy(Point middle, Sprite* s, int health, float speed);
	~BaseEnemy();
	void takeDamage(int damage);
	virtual void think() override;
protected:
	int health;
	float speed;
	PointItr nextPoint;
private:
	void move();
};

