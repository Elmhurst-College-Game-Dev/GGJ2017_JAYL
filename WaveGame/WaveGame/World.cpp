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

struct rect
{
	Point topLeft;
	Point bottomRight;
	rect(Point p1, Point p2)
	{
		topLeft = p1;
		bottomRight = p2;
	}
};

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

	possiblePlacements.emplace_back(Point(211.0, 122.0), Point(350.0, 336.0));
	possiblePlacements.emplace_back(Point(284.0, 359.0), Point(350.0, 611.0));
	possiblePlacements.emplace_back(Point(434.0, 214.0), Point(564.0, 448.0));
	possiblePlacements.emplace_back(Point(430.0, 466.0), Point(518.0, 710.0));
	possiblePlacements.emplace_back(Point(590.0, 558.0), Point(782.0, 610.0));
	possiblePlacements.emplace_back(Point(648.0, 126.0), Point(786.0, 574.0));
	possiblePlacements.emplace_back(Point(704.0, 122.0), Point(994.0, 164.0));
	possiblePlacements.emplace_back(Point(874.0, 272.0), Point(938.0, 712.0));
	possiblePlacements.emplace_back(Point(1028.0, 122.0), Point(1180.0, 298.0));
	possiblePlacements.emplace_back(Point(1028.0, 332.0), Point(1062.0, 588.0));
	possiblePlacements.emplace_back(Point(1202.0, 486.0), Point(1278.0, 666.0));
	possiblePlacements.emplace_back(Point(1202.0, 120.0), Point(1276.0, 290.0));
	possiblePlacements.emplace_back(Point(188.0, 683.0), Point(522.0, 712.0));

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

bool World::canPlaceTower(Point p)
{
	for (auto rect : possiblePlacements)
	{
	//	printf("checking point in rect %f %f, %f %f\n", rect.topLeft.x, rect.topLeft.y, rect.bottomRight.x, rect.bottomRight.y);

		if (p.inBox(rect.topLeft, rect.bottomRight))
		{
			for (auto ent : *getTowers())
			{
				Point entMiddle = ent->getMiddle();
				Point topLeft = Point(entMiddle.x - (ent->getWidth() / 2.0), entMiddle.y + (ent->getHeight() / 2.0));
				Point bottomRight = Point((entMiddle.x + (ent->getWidth() / 2.0)), (entMiddle.y - (ent->getHeight() / 2.0)));
				if (p.inBox(topLeft, bottomRight))
				{
					cout << "In tower, returning false" << endl;
					return false;
				}
			}
	//		cout << "In area. not in any towers." << endl;
			return true;
		}
	}
//	cout << "Not in any area." << endl;
	return false;
}

#endif