#ifndef __IMAGE_LOADING__
#define __IMAGE_LOADING__

#ifndef __glew.h__
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include <IL/il.h>

GLuint loadTexture(const char *file);
void deleteTexture(GLuint tex);
void InitIL();

#endif