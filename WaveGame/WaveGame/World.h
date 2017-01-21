#ifndef _WORLD_INCLUDED
#define _WORLD_INCLUDED

#include <list>
#include <map>
#include "Sprite.h"
#include "Point.h"

using namespace std;

#define STARTING_SPAWNS 10

class BaseObject;
class BaseEnemy;
class BaseTurret;

enum Upgrade
{
	U_Radio = 0,
	U_Micro,
	U_Infrared,
	U_Visible,
	U_Ultraviolet,
	U_Xray,
	U_Gamma,
	U_Cosmic
};

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
	const list<BaseObject* > * getTowers();
	const list<Point> * getPath();
	Point getEndPoint();
	void damagePlayer();
	void upgradeTurret(BaseTurret* turret);
	inline bool canUpgradeTurret(BaseTurret* turret);

private:
	std::list<Point> path;

	std::list<BaseEnemy *> enemies;
	std::list<BaseObject *> towers;

	unsigned int lives;
	unsigned int currentWave = 0;

	unsigned int duration = 30;
	unsigned long long currentFrame;
	unsigned long long nextSpawnFrame;
	unsigned int remainingSpawns = STARTING_SPAWNS;
	unsigned long long framesBetweenSpawns;

	unsigned int money;

	void spawnEnemy();

	map<Upgrade, Sprite> ssSprites;
	map<Upgrade, Sprite> areaSprites;
};

#endif