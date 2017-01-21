#ifndef __SHADERS_CPP__
#define __SHADERS_CPP__

#include "shaders.h"
#include <stdlib.h>
#include <stdio.h>

GLuint loadShader(const GLchar *source, GLenum type) {
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	GLint param;
	char *log;
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &param);
	if (param == GL_FALSE) {
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &param);
		log = (char*)malloc(param + 1);
		glGetShaderInfoLog(shader, param + 1, NULL, log);
		log[param] = '\0';
		fprintf(stderr, "Error compiling shader:\n%s\n", log);
		free(log);
		return 0;
	}
	return shader;
}

GLuint linkProgram(GLuint vert, GLuint frag) {
	GLuint program = glCreateProgram();
	glAttachShader(program, vert);
	glAttachShader(program, frag);
	glLinkProgram(program);
	GLint param;
	char *log;
	glGetProgramiv(program, GL_LINK_STATUS, &param);
	if (param == GL_FALSE) {
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &param);
		log = (char*)malloc(param + 1);
		glGetProgramInfoLog(program, param + 1, NULL, log);
		fprintf(stderr, "Error linking shader:\n%s\n", log);
		free(log);
		return 1;
	}
	return program;
}

#endif 