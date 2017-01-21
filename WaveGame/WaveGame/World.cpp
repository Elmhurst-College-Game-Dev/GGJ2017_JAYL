#include "World.h"
#include <assert.h>

#include "BaseEnemy.h"

#define FRAMERATE 30

// TODO: Parameters for lives? waves?
World::World()
{
	// TODO: Define path.
}


World::~World()
{
	for (auto ent : enemies)
	{
		delete ent;
	}

	for (auto ent : towers)
	{
		delete ent;
	}
}

void World::think()
{
	if (currentFrame = nextSpawnFrame)
	{
		spawnEnemy();

		nextSpawnFrame += framesBetweenSpawns;
	}

	for (auto ent : towers)
	{
		ent->think();
	}

	for (auto ent = enemies.begin(); ent != enemies.end(); ent++)
	{
		if ((*ent)->getHealth() > 0)
		{
			(*ent)->think();
		}
		else
		{
			enemies.erase(ent);
		}
	}

	if (lives == 0)
	{
		// TODO: something when you lose
		//YouLose();
	}
	else if (enemies.size() == 0)
	{
		// TODO: Decide last wave.
		if (currentWave == 100000 /*LAST_WAVE*/)
		{
			// TODO: Something when you win
			//YouWin();
		}
		else
		{
			startWave();
		}
	}
	currentFrame++;
}

void World::spawnEnemy()
{
	// TODO: Figure out how spawns work.

}

void World::addTower(BaseObject * ent)
{
	towers.push_back(ent);
}

void World::addEnemy(BaseEnemy* ent)
{
	enemies.push_back(ent);
}

const list<BaseEnemy*> * World::getEnemies()
{
	return &enemies;
}

void World::startWave()
{
	assert(enemies.size() == 0);
	remainingSpawns = (remainingSpawns * 2) + 5;

	framesBetweenSpawns = (duration * FRAMERATE) / remainingSpawns;
}

unsigned long long World::getFrameCount()
{
	return currentFrame;
}

const list<Point> * World::getPath()
{
	return &path;
}

Point World::getEndPoint()
{
	assert(path.size() != 0);
	return (*(path.cend()--));
}

void World::damagePlayer()
{
	lives--;
}