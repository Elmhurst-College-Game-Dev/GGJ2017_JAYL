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

	path.emplace_back(200.0, 415.0);
	path.emplace_back(240.0, 420.0);
	path.emplace_back(245.0, 620);
	path.emplace_back(280.0, 665.0);
	path.emplace_back(389.0, 647.0);
	path.emplace_back(400.0, 180.0);
	path.emplace_back(590.0, 177.0);
	path.emplace_back(600.0, 190.0);
	path.emplace_back(600.0, 501.0);
	path.emplace_back(560.0, 520.0);
	path.emplace_back(825.0, 651.0);
	path.emplace_back(825.0, 223.0);
	path.emplace_back(971.0, 650.0);
	path.emplace_back(1125.0, 650.0);
	path.emplace_back(1125.0, 407.0);
	path.emplace_back(1247.0, 407.0);


	possiblePlacements.emplace_back(220.0, 315.0);
	possiblePlacements.emplace_back(255.0, 315.0);
	possiblePlacements.emplace_back(305.0, 370.0);
	possiblePlacements.emplace_back(337.0, 370.0);
	possiblePlacements.emplace_back(305.0, 410.0);
	possiblePlacements.emplace_back(337.0, 410.0);
	possiblePlacements.emplace_back(305.0, 450.0);
	possiblePlacements.emplace_back(337.0, 450.0);
	possiblePlacements.emplace_back(305.0, 490.0);
	possiblePlacements.emplace_back(337.0, 490.0);
	possiblePlacements.emplace_back(305.0, 530.0);
	possiblePlacements.emplace_back(337.0, 530.0);
	possiblePlacements.emplace_back(305.0, 570.0);
	possiblePlacements.emplace_back(337.0, 570.0);
	possiblePlacements.emplace_back(337.0, 330.0);
	possiblePlacements.emplace_back(305.0, 330.0);
	possiblePlacements.emplace_back(337.0, 290.0);
	possiblePlacements.emplace_back(337.0, 250.0);
	possiblePlacements.emplace_back(337.0, 210.0);
	possiblePlacements.emplace_back(337.0, 170.0);

	possiblePlacements.emplace_back(453.0, 650.0);
	possiblePlacements.emplace_back(453.0, 610.0);
	possiblePlacements.emplace_back(453.0, 570.0);
	possiblePlacements.emplace_back(453.0, 530.0);
	possiblePlacements.emplace_back(453.0, 490.0);
	possiblePlacements.emplace_back(453.0, 450.0);
	possiblePlacements.emplace_back(453.0, 410.0);
	possiblePlacements.emplace_back(453.0, 370.0);
	possiblePlacements.emplace_back(453.0, 330.0);
	possiblePlacements.emplace_back(453.0, 290.0);
	possiblePlacements.emplace_back(453.0, 250.0);

	possiblePlacements.emplace_back(487.0, 650.0);
	possiblePlacements.emplace_back(487.0, 610.0);
	possiblePlacements.emplace_back(487.0, 570.0);
	possiblePlacements.emplace_back(487.0, 530.0);
	possiblePlacements.emplace_back(487.0, 490.0);
	
	possiblePlacements.emplace_back(520.0, 440.0);
	possiblePlacements.emplace_back(550.0, 440.0);
	possiblePlacements.emplace_back(550.0, 400.0);
	possiblePlacements.emplace_back(550.0, 360.0);
	possiblePlacements.emplace_back(550.0, 320.0);
	possiblePlacements.emplace_back(550.0, 280.0);
	possiblePlacements.emplace_back(550.0, 240.0);
	possiblePlacements.emplace_back(515.0, 240.0);
	possiblePlacements.emplace_back(480.0, 240.0);

	possiblePlacements.emplace_back(670.0, 150.0);
	possiblePlacements.emplace_back(670.0, 190.0);
	possiblePlacements.emplace_back(670.0, 230.0);
	possiblePlacements.emplace_back(670.0, 270.0);
	possiblePlacements.emplace_back(670.0, 310.0);
	possiblePlacements.emplace_back(670.0, 350.0);
	possiblePlacements.emplace_back(670.0, 390.0);
	possiblePlacements.emplace_back(670.0, 430.0);
	possiblePlacements.emplace_back(670.0, 470.0);
	possiblePlacements.emplace_back(670.0, 510.0);
	possiblePlacements.emplace_back(670.0, 550.0);

	possiblePlacements.emplace_back(615.0, 570);
	possiblePlacements.emplace_back(645.0, 570);

	possiblePlacements.emplace_back(615.0, 605);
	possiblePlacements.emplace_back(655.0, 605);
	possiblePlacements.emplace_back(690.0, 605);
	possiblePlacements.emplace_back(730.0, 605);
	possiblePlacements.emplace_back(770.0, 605);

	possiblePlacements.emplace_back(770.0, 565);
	possiblePlacements.emplace_back(770.0, 525);
	possiblePlacements.emplace_back(770.0, 485);
	possiblePlacements.emplace_back(770.0, 445);
	possiblePlacements.emplace_back(770.0, 405);
	possiblePlacements.emplace_back(770.0, 365);
	possiblePlacements.emplace_back(770.0, 325);
	possiblePlacements.emplace_back(770.0, 285);
	possiblePlacements.emplace_back(770.0, 245);
	possiblePlacements.emplace_back(770.0, 205);
	possiblePlacements.emplace_back(770.0, 165);

	possiblePlacements.emplace_back(810.0, 165);

	cout << (*path.begin()).x << endl;

	// TODO: Define possible tower placements
	wavePoints.push_back(Point(0.0, 0.0));
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
	cout << "currentFrame " << currentFrame << " nextSpawn" << nextSpawnFrame << endl;
	if (currentFrame == nextSpawnFrame)
	{
		cout << "Spawning enemy" << endl;
		spawnEnemy();
		cout << "Successful spawn" << endl;
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
	addEnemy(new BaseEnemy(spawn, renderController.get(info[0].sprite), 32.0f, 32.0f, info[i].health, info[i].speed, i));
}

void World::addTower(BaseTurret * ent, Point p)
{
	possiblePlacements.remove(p);
	addTower(ent);
}

void World::addTower(BaseTurret * ent)
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
	return path.back();
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

list<Point> * World::getPossiblePlacements()
{
	return &possiblePlacements;
}

#endif