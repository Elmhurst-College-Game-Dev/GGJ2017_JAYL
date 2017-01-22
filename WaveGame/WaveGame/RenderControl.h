#pragma once

#include "Sprite.h"
#include "BaseObject.h"
#include <map>

class RenderControl
{
public:
	RenderControl();
	~RenderControl();
	void initRender();
	void initShaders();
	void initTextureWithData(const char *dataFile, const char *textureFile, 
		float texWidth, float texHeight);
	Sprite &get(string sprite);
	GLuint getProgram() { return program;  }
	GLuint getModelLoc() { return modelLoc;  }
	GLuint getSizeLoc() { return sizeLoc; }
	GLuint getWorldPosLoc() { return worldPosLoc; }
	GLuint getVertPosLoc() { return vertPosLoc;  }
	GLuint getTexCoordLoc() { return texCoordLoc;  }
	GLuint getSamplerLoc() { return samplerLoc;  }
	map<string, Sprite> &getSprites() { return sprites;  }
private:
	GLuint program;
	GLuint modelLoc;
	GLuint sizeLoc;
	GLuint worldPosLoc;
	GLuint vertPosLoc;
	GLuint texCoordLoc;
	GLuint samplerLoc;
	map<string, Sprite> sprites;
};

