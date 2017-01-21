#pragma once

#include "Sprite.h"
#include "BaseObject.h"
#include <map>

class RenderControl
{
public:
	RenderControl();
	~RenderControl();
	void draw(BaseObject &obj);
	void initRender();
private:
	GLuint program;
	GLuint viewLoc;
	GLuint worldPosLoc;
	GLuint sizeLoc;
	GLuint vertPosLoc;
	GLuint texCoordLoc;
	GLuint samplerLoc;
	map<string, GLuint> imageIndexLocations;
	GLuint arrayBufferName;
	GLuint indexArrayBufferName;
};

