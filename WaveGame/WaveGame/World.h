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

class World
{
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
	const list<Point> * getPath();
	const list<Point> * getPossiblePlacements();
	Point getEndPoint();
	void damagePlayer();
	void upgradeTurret(BaseTurret* turret);
	inline bool canUpgradeTurret(BaseTurret* turret);

	BaseTurret * selected;
	BaseTurret * purchasing;
private:
	std::list<Point> path;
	std::list<Point> possiblePlacements;

	BaseObject * wave;
	std::list<BaseEnemy *> enemies;
	std::list<BaseTurret *> towers;
	std::list<ButtonObject *> buttons;

	unsigned int lives;
	unsigned int currentWave = 0;

	unsigned int duration = 30;
	unsigned long long currentFrame;
	unsigned long long nextSpawnFrame;
	unsigned int remainingSpawns = STARTING_SPAWNS;
	unsigned long long framesBetweenSpawns;
	unsigned int enemiesUnlocked;

	unsigned int money;

	void spawnEnemy();
	vector<Point> wavePoints;

	vector<string> enemySprites;
	vector<EnemyInfo> info;
};

#endif