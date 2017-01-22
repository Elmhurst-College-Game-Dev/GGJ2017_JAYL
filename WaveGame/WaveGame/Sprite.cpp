#include "RenderControl.h"
#include "GLFW/glfw3.h"
#include <cmath>
#include <iostream>

extern RenderControl renderController;

using namespace std;

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

Sprite & Sprite::operator=(const Sprite & rhs)
{
	bufferOffset = rhs.bufferOffset;
	bufferName = rhs.bufferName;
	textureName = rhs.textureName;
	return *this;
}

void Sprite::draw(float angle, float width, float height, float worldPosX, float worldPosY)
{
	glUseProgram(renderController.getProgram());
	GLfloat modelView[9]{
		static_cast<float>(cos(angle)), -static_cast<float>(sin(angle)), 0.0f,
		static_cast<float>(sin(angle)), static_cast<float>(cos(angle)), 0.0f,
		0.0f, 0.0f, 1.0f
	};
	if (bufferName == 0 || textureName == 0) {
		cout << "THIS OBJECT CANNOT BE DRAWN: INVALID" << endl;
	}
	glUniformMatrix3fv(renderController.getModelLoc(), 1, GL_TRUE, modelView);
	glUniform2f(renderController.getSizeLoc(), width, height);
	glUniform2f(renderController.getWorldPosLoc(), worldPosX, worldPosY);
	glEnableVertexAttribArray(renderController.getVertPosLoc());
	glEnableVertexAttribArray(renderController.getTexCoordLoc());
	glVertexAttribPointer(renderController.getVertPosLoc(), 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, 0);
	glVertexAttribPointer(renderController.getTexCoordLoc(), 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (void*)(sizeof(GLfloat) * 2));
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(renderController.getSamplerLoc(), 0);
	glBindTexture(GL_TEXTURE_2D, textureName);
	glBindBuffer(GL_ARRAY_BUFFER, bufferName);
	glDrawArrays(GL_TRIANGLES, bufferOffset, 6);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindTexture(GL_TEXTURE_2D, 0);
	glDisableVertexAttribArray(renderController.getVertPosLoc());
	glDisableVertexAttribArray(renderController.getTexCoordLoc());
}
