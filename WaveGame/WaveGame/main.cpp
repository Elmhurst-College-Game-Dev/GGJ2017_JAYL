
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <IL/il.h>
#include <iostream>
#include "RenderControl.h"

using namespace std;

int main() {

	if (!glfwInit()) {
		cout << "Could not init GLFW" << endl;
		return 1;
	}
	GLFWwindow *win = glfwCreateWindow(1280, 720, "Wave Game", nullptr, nullptr);
	glfwMakeContextCurrent(win);
	GLenum status = glewInit();
	if (status != GLEW_OK) {
		cout << "Did not initialize OpenGL properly" << endl;
		return 5;
	}
	RenderControl renderController;
	while (!glfwWindowShouldClose(win)) {
		//Update code here

		//Render code here


		glfwShowWindow(win);
		glfwPollEvents();
	}

	return 0;
}