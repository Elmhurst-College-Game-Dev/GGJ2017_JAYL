#pragma once

#include "Sprite.h"
#include "BaseObject.h"
#include <map>

class RenderControl
{
public:
	RenderControl();
	~RenderControl();
	void draw(BaseObject *obj);
	void draw(BaseEnemy *obj);
	void initRender();
	Sprite &get(int index);
private:
	GLuint program;
	GLuint viewLoc;
	GLuint worldPosLoc;
	GLuint sizeLoc;
	GLuint vertPosLoc;
	GLuint texCoordLoc;
	GLuint samplerLoc;
	GLuint angleLoc;
	map<int, Sprite> sprites;
	GLuint arrayBufferName;
	GLuint indexArrayBufferName;
};

