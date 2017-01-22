#include "WaveObject.h"
#include "RenderControl.h"
#include "Point.h"
#include <cmath>

extern RenderControl renderController;

WaveObject::WaveObject(int startX, int maxX) : 
	BaseObject(Point(float(startX), 420.0f), renderController.get("Assets/WaveSprite-0"), 
		141, 600)
{
	this->startX = startX;
	this->maxX = maxX;
	sinWave = 0;
}

Point WaveObject::getRandomSpawnPoint()
{
	return Point();
}

void WaveObject::think()
{
	sinWave += (3.141f / 80.0f);
	if (sinWave > (3.141 * 2)) {
		sinWave = 0.0f;
	}
	cout << sinWave << endl;
	middle = Point(startX + (float(maxX-startX)*sin(sinWave)), middle.y);
	
}
