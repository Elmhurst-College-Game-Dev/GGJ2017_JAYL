
#ifndef __glew.h__
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include <IL/il.h>
#include <iostream>
#include "RenderControl.h"
#include "BaseEnemy.h"
#include "image_loading.h"
#include "ButtonObject.h"

#define MILLISECONDS_PER_FRAME 33

using namespace std;

#include "World.h"
World* world;
RenderControl renderController;

void OnMouseButton(GLFWwindow* win, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		double x, y;
		glfwGetCursorPos(win, &x, &y);

		for (auto ent : *(world->getTowers()))
		{
			Point middle = ent->getMiddle();
			Point topLeft = Point(middle.x - (ent->getWidth() / 2.0), middle.y + (ent->getHeight() / 2.0));
			Point bottomRight = Point(middle.x + (ent->getWidth() / 2), middle.y - (ent->getHeight() / 2.0));
			if (middle.inBox(topLeft, bottomRight))
			{
				world->selected = ent;
			}
		}

		for (auto ent : *(world->getButtons()))
		{
			Point middle = ent->getMiddle();
			Point topLeft = Point(middle.x - (ent->getWidth() / 2.0), middle.y + (ent->getHeight() / 2.0));
			Point bottomRight = Point(middle.x + (ent->getWidth() / 2), middle.y - (ent->getHeight() / 2.0));
			if (middle.inBox(topLeft, bottomRight))
			{
				world->selected = ent;
			}
		}
	}
}

int main() {
	vector<string> sprites{ "sprite1", "sprite2", "sprite3", "sprite4", "sprite5" };
	world = new World(sprites);
	
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
	InitIL();
	renderController.initRender();

	glfwSwapInterval(1);

	glfwSetMouseButtonCallback(win, OnMouseButton);

	while (!glfwWindowShouldClose(win)) {
		//Update code here

		//Render code here
		glClear(GL_COLOR_BUFFER_BIT);
		//Draw all objects
		for (list<BaseEnemy*>::const_iterator itr = world->getEnemies()->cbegin(); itr != world->getEnemies()->cend(); itr++) {
			renderController.draw(*itr);
		}
		for (list<BaseObject*>::const_iterator itr = world->getTowers()->cbegin(); itr != world->getTowers()->cend(); itr++) {
			renderController.draw(*itr);
		}

		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	return 0;
}