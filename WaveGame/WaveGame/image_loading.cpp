#ifndef __IMAGE_LOADING_CPP__
#define __IMAGE_LOADING_CPP__

#include "image_loading.h"

GLuint loadTexture(const char *file) {

	bool success;
	unsigned int imageName;

	//Read the DevIL documentation
	ilGenImages(1, &imageName);
	ilBindImage(imageName);
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);

	success = ilLoadImage(file);
	if (!success) {
		ilDeleteImage(imageName);
		printf("Unable to load image: %s\n", file);
		return 0;
	}

	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	GLuint tex;
	glGenTextures(1, &tex);
	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int height = ilGetInteger(IL_IMAGE_HEIGHT);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
	glTexSubImage2D(GL_TEXTURE_2D,
		0,
		0, 0,
		width, height,
		GL_RGBA, GL_UNSIGNED_BYTE,
		ilGetData());
	ilDeleteImage(imageName);
	ilBindImage(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	return tex;
}

void deleteTexture(GLuint tex) {
	glDeleteTextures(1, &tex);
}

#endif