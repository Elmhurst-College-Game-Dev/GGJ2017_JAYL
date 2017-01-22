#pragma once

#ifndef __glew.h__
#include <GL/glew.h>
#endif

#include <vector>

using namespace std;

class Sprite
{
public:
	explicit Sprite(GLint bufferOffset, GLuint bufferName, GLuint textureName);
	Sprite(const Sprite &spr);
	Sprite();
	void setTextureName(GLuint texName);
	void setBufferName(GLuint bufName);
	void setBufferOffset(GLint bufOffset);
	GLuint getTextureName() { return textureName;  }
	GLuint getBufferName() { return bufferName;  }
	GLuint getBufferOffset() { return bufferOffset;  }
	void draw(float angle, float width, float height, float worldPosX, float worldPosY);
private:
	GLuint textureName;
	GLuint bufferName;
	GLint bufferOffset;
};

