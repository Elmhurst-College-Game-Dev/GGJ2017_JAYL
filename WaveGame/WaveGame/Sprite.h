#pragma once

#ifndef __glew.h__
#include <GL/glew.h>
#endif

#include <vector>

using namespace std;

class Sprite
{
public:
	Sprite(vector<GLuint> track);
	Sprite(GLuint img);
	Sprite() = default;
	Sprite(const Sprite &rhs);
	~Sprite();
	void* getOffset();
	int getFrameSpeed() const { return frameSpeed;  }
	void setFrameSpeed(int frameSpeed) { this->frameSpeed = frameSpeed;  }
	void updateSpriteAnimation();
private:
	int indexOffset; //current
	vector<GLuint> animationTrack;
	int frameSpeed; //The number of updates before the track changes
	int timer;
};

