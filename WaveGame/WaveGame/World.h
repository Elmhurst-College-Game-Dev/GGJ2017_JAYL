#ifndef _WORLD_INCLUDED
#define _WORLD_INCLUDED

#include <list>
#include <vector>
#include <string>
#include <map>
#include "Sprite.h"
#include "Point.h"
#include <iostream>

using namespace std;

#define STARTING_SPAWNS 10

class BaseObject;
class BaseEnemy;
class BaseTurret;
class ButtonObject;

enum ButtonType;

struct EnemyInfo
{
	int health;
	float speed;
	string sprite;
	EnemyInfo(int he, float spe, string spr)
	{
		health = he;
		speed = spe;
		sprite = spr;
	}
};

using PlacementSpot = list<Point>::iterator;

class World
{
private:
	struct Rect
	{
	public:
		Point topLeft;
		Point bottomRight;
		Rect(Point p1, Point p2)
		{
			topLeft = p1;
			bottomRight = p2;
		}
	};
public:
	// TODO: Parameters for lives? waves?
	World(vector<string> enemySprites);
	~World();

	void addTower(BaseTurret * ent);
	void addEnemy(BaseEnemy * ent);
	void addEnemyInfo(EnemyInfo info);
	void addButton(ButtonObject * ent);
	void think();
	void startWave();
	unsigned long long getFrameCount();
	const list<BaseEnemy* > * getEnemies();
	const list<BaseTurret * > * getTowers();
	list<ButtonObject *> * getButtons();
	const vector<Point> &getPath();
	Point getEndPoint();
	void damagePlayer();
	void upgradeTurret(BaseTurret* turret);
	inline bool canUpgradeTurret(BaseTurret* turret);
	bool canPlaceTower(Point p);
	bool deductHealth() {
		health--;
		if (health <= 0) {
			//End game
			cout << "LOSE" << endl;
			lose();
			return true;
		}
		return false;
	}

	inline unsigned int getMoney() { return money;  }
	inline unsigned int getEnemiesLeft() { return enemies.size();  }
	inline unsigned int getHealth() { return health;  }
	inline void subtractMoney(unsigned int sub) { money -= sub; }
	void lose() { lostGame = true;  }
	bool lost() { return lostGame; }
	BaseTurret * selected;
	BaseTurret * purchasing;
private:
	std::vector<Point> path;
	std::list<Rect> possiblePlacements;
	const float spotWidth = 32.0f;
	const float spotHeight = 32.0f;

	BaseObject * wave;
	std::list<BaseEnemy *> enemies;
	std::list<BaseTurret *> towers;
	std::list<ButtonObject *> buttons;

	unsigned int lives;
	unsigned int currentWave = 0;
	unsigned int startSpawns = 15;
	unsigned int duration = 30;
	unsigned long long currentFrame;
	unsigned long long nextSpawnFrame;
	unsigned int remainingSpawns = STARTING_SPAWNS;
	unsigned long long framesBetweenSpawns;
	unsigned int enemiesUnlocked;

	bool lostGame = false;
	unsigned int money = 3000;
	unsigned int health = 3;

	void spawnEnemy();
	vector<Point> wavePoints;

	vector<string> enemySprites;
	vector<EnemyInfo> info;
};

#endif