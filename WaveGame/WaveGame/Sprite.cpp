#ifndef __SPRITE_CPP__
#define __SPRITE_CPP__

#include <iostream>
#include "Sprite.h"

using namespace std;

Sprite::Sprite(GLuint img) : animationTrack()
{
	animationTrack.push_back(img);
	indexOffset = 0 ;
}

Sprite::Sprite(vector<GLuint> track) : animationTrack( track )
{
	indexOffset = 0;
}

Sprite::Sprite(const Sprite & rhs)
{
	indexOffset = rhs.indexOffset;
	animationTrack = rhs.animationTrack;
	frameSpeed = rhs.frameSpeed;
	timer = 0;
}

Sprite::~Sprite()
{
}

void* Sprite::getOffset()
{
	if (animationTrack.size() == 0)
		cout << "HEY YOU HAVE AN EMPTY ANIMATION TRACK YOU DUMMY" << endl;
	return (void*)animationTrack[indexOffset];
}

void Sprite::updateSpriteAnimation()
{
	if (animationTrack.size() > 1) {
		timer++;
		if (timer > frameSpeed) {
			timer = 0;
			indexOffset++;
			if (indexOffset >= animationTrack.size()) {
				indexOffset = 0;
			}
		}
	}
}


#endif