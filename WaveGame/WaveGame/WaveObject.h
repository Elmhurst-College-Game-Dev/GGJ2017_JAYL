#pragma once

#include "BaseObject.h"

//Moves back and forth and used for getting spawn points

class WaveObject : public BaseObject {
public:
	WaveObject(int startX, int maxX);
	Point getRandomSpawnPoint();
	void think() override;
private:
	float sinWave;
	int startX;
	int maxX;
};