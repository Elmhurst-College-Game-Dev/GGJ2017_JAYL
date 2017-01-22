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
	void initTextureWithData(const char *dataFile, const char *textureFile);
	Sprite &get(string sprite);
	GLuint getProgram() { return program;  }
	GLuint getModelLoc() { return modelLoc;  }
	GLuint getScaleLoc() { return scaleLoc; }
	GLuint getTranslateLoc() { return translateLoc; }
	GLuint getVertPosLoc() { return vertPosLoc;  }
	GLuint getTexCoordLoc() { return texCoordLoc;  }
	GLuint getSamplerLoc() { return samplerLoc;  }
	
private:
	GLuint program;
	GLuint modelLoc;
	GLuint scaleLoc;
	GLuint translateLoc;
	GLuint vertPosLoc;
	GLuint texCoordLoc;
	GLuint samplerLoc;
	map<string, Sprite> sprites;
};

