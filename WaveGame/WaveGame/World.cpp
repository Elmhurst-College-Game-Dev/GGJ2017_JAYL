#ifndef __WORLD_CPP__
#define __WORLD_CPP__

#include "World.h"
#include <assert.h>
#include "RenderControl.h"
#include "BaseEnemy.h"
#include "BaseTurret.h"
#include "ButtonObject.h"
#include <iostream>

#define FRAMERATE 30

extern RenderControl renderController;

// TODO: Parameters for lives? waves?
World::World(vector<string> sprites)
{
	// TODO: Define path.
	enemySprites = sprites;

	// TODO: Define possible tower placements
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
	unsigned int i = rand() % enemiesUnlocked;
	// TODO: Magic math to determine start point
//	float x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 190);
//	float y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX / 720);

	Point spawn = wave->getMiddle() + wavePoints[rand() * (wavePoints.size() - 1)];
	enemies.push_back(new BaseEnemy(spawn, renderController.get(info[i].sprite), 32.0f, 32.0f, info[i].health, info[i].speed, i));
}

void World::addTower(BaseTurret * ent)
{
	towers.push_back(ent);
	cout << "after pushing" << ent->getMiddle().x << ent->getMiddle().y << endl;
}

void World::addEnemy(BaseEnemy* ent)
{
	enemies.push_back(ent);
}

const list<BaseEnemy*> * World::getEnemies()
{
	return &enemies;
}

const list<BaseTurret *> * World::getTowers()
{
	return &towers;
}

list<ButtonObject *> * World::getButtons()
{
	return &buttons;
}

void World::startWave()
{
	assert(enemies.size() == 0);
	remainingSpawns = (remainingSpawns * 2) + 5;

	framesBetweenSpawns = (duration * FRAMERATE) / remainingSpawns;
	
	if (currentWave % 2 == 0 && enemiesUnlocked < 4)
	{
		enemiesUnlocked++;
	}
	
	currentWave++;
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

void World::upgradeTurret(BaseTurret* turret)
{
	assert(canUpgradeTurret(turret));
	money -= turret->getUpgradePrice();
	turret->upgrade();
}

bool World::canUpgradeTurret(BaseTurret* turret)
{
	return money >= turret->getUpgradePrice();
}

void World::addEnemyInfo(EnemyInfo info)
{
	this->info.push_back(info);
}

void World::addButton(ButtonObject * button)
{
	buttons.push_back(button);
}

const list<Point> * World::getPossiblePlacements()
{
	return &possiblePlacements;
}

void World::iterate()
{
	for (auto ent : buttons)
	{
		std::cout << (*ent).getMiddle().x << endl;
	}
}

#endif