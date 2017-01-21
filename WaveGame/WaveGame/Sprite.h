#pragma once

#ifndef __glew.h__
#include <GL/glew.h>
#endif

class Sprite
{
public:
	explicit Sprite(GLuint initialOffset);
	Sprite();
	Sprite(const Sprite &rhs);
	~Sprite();
	void* getOffset();
private:
	GLuint indexOffset; //current
	
};

