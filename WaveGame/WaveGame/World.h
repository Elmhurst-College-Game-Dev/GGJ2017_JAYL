#pragma once

#include <list>
#include "BaseObject.h"
#include "BaseEnemy.h"
#include "Point.h"

using namespace std;

#define STARTING_SPAWNS 10

class World
{
public:
	// TODO: Parameters for lives? waves?
	World();
	~World();

	void addTower(BaseObject * ent);
	void addEnemy(BaseEnemy * ent);
	void think();
	void startWave();
	unsigned long long getFrameCount();
	const list<BaseEnemy* > * getEnemies();

private:
	std::list<Point> path;

	std::list<BaseEnemy *> enemies;
	std::list<BaseObject *> towers;

	unsigned int lives;
	unsigned int currentWave = 0;

	int duration = 30;
	unsigned long long currentFrame;
	unsigned long long nextSpawnFrame;
	int remainingSpawns = STARTING_SPAWNS;
	unsigned long long framesBetweenSpawns;

	void spawnEnemy();
};

