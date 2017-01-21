#ifndef __SPRITE_CPP__
#define __SPRITE_CPP__

#include "Sprite.h"

Sprite::Sprite() : indexOffset{ 0 } {

}

Sprite::Sprite(GLuint initialOffset) : indexOffset{initialOffset}
{
}

Sprite::Sprite(const Sprite & rhs)
{
	indexOffset = rhs.indexOffset;
}

Sprite::~Sprite()
{
}

void* Sprite::getOffset()
{
	return (void*)indexOffset;
}


#endif