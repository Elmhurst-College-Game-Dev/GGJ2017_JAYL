#ifndef __SHADERS__
#define __SHADERS__

#ifndef __glew.h__
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>

GLuint loadShader(const GLchar *source, GLenum type);
GLuint linkProgram(GLuint vert, GLuint frag);

#endif
