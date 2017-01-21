#ifndef __SPRITE_CPP__
#define __SPRITE_CPP__

#include "Sprite.h"

Sprite::Sprite(GLuint initialOffset) : indexOffset{initialOffset}
{
}

Sprite::~Sprite()
{
}

void* Sprite::getOffset()
{
	return (void*)indexOffset;
}


#endif