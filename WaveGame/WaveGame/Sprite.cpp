#include "RenderControl.h"
#include "GLFW/glfw3.h"
#include <cmath>
#include <iostream>

extern RenderControl renderController;

Sprite::Sprite(GLint bufferOffset, GLuint bufferName, GLuint textureName) 
	: bufferOffset{bufferOffset}, bufferName{bufferName}, textureName{textureName}
{

}

Sprite::Sprite(const Sprite & spr)
{
	bufferOffset = spr.bufferOffset;
	bufferName = spr.bufferName;
	textureName = spr.textureName;
}

Sprite::Sprite()
{
//	std::cout << "Sprite detaul constructor called" << std::endl;
	bufferName = 0;
	bufferOffset = 0;
	textureName = 0;
}

void Sprite::setTextureName(GLuint texName)
{
	this->textureName = texName;
}

void Sprite::setBufferName(GLuint bufName)
{
	this->bufferName = bufName;
}

void Sprite::setBufferOffset(GLint bufOffset)
{
	this->bufferOffset = bufOffset;
}

void Sprite::draw(float angle, float width, float height, float worldPosX, float worldPosY)
{
	glUseProgram(renderController.getProgram());
	float angleCos = cos(angle);
	float angleSin = sin(angle);
	GLfloat modelView[9]{
		width*angleCos, -height*angleSin, worldPosX - 640.0f,
		width*angleSin, height*angleCos, -(worldPosY - 360.0f),
		0.0f, 0.0f, 1.0f
	};
	/*cout << modelView[0] << ", " << modelView[1] << ", " << modelView[2] << ", " << endl
	<< modelView[3] << ", " << modelView[4] << ", " << modelView[5] << ", " << endl
	<< modelView[6] << ", " << modelView[7] << ", " << modelView[8] << endl <<
	(int)obj->getSprite().getOffset() << endl;*/
	glUniformMatrix3fv(renderController.getModelLoc(), 1, GL_TRUE, modelView);
	glVertexAttribPointer(renderController.getVertPosLoc(), 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, 0);
	glVertexAttribPointer(renderController.getTexCoordLoc(), 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void*)(sizeof(GLfloat) * 2));
	glEnableVertexAttribArray(renderController.getVertPosLoc());
	glEnableVertexAttribArray(renderController.getTexCoordLoc());
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(renderController.getSamplerLoc(), 0);
	glBindTexture(GL_TEXTURE_2D, textureName);
	glBindBuffer(GL_ARRAY_BUFFER, bufferName);
	glDrawArrays(GL_TRIANGLES, bufferOffset, 6);
}
