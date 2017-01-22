
#ifndef __glew.h__
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include <IL/il.h>
#include <iostream>
#include "RenderControl.h"
#include "BaseEnemy.h"
#include "image_loading.h"
#include "BaseTurret.h"
#include "ButtonObject.h"
#include "StraightTurret.h"
#include <assert.h>

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

		cout << "click at " << x << " " << y << endl;

		BaseTurret * clicked = nullptr;

		for (auto ent : *(world->getTowers()))
		{
			Point clickSpot(static_cast<float>(x), static_cast<float>(y));

			Point entMiddle = ent->getMiddle();

			Point topLeft = Point(entMiddle.x - (ent->getWidth() / 2.0), entMiddle.y + (ent->getHeight() / 2.0));
			Point bottomRight = Point(entMiddle.x + (ent->getWidth() / 2), entMiddle.y - (ent->getHeight() / 2.0));

			if (clickSpot.inBox(topLeft, bottomRight))
			{
				assert(false);
				clicked = ent;
			}
		}

		if (world->selected != nullptr)
		{
			for (auto ent : *(world->getButtons()))
			{
				Point middle = ent->getMiddle();
				Point topLeft = Point(middle.x - (ent->getWidth() / 2.0), middle.y + (ent->getHeight() / 2.0));
				Point bottomRight = Point(middle.x + (ent->getWidth() / 2), middle.y - (ent->getHeight() / 2.0));
				
				if (middle.inBox(topLeft, bottomRight)) // clicked inside button
				{
					if (action == GLFW_RELEASE) // releasing m1 inside button
					{
						if (ent->getType() == BT_Upgrade) // Upgrade
						{
							if (world->canUpgradeTurret(world->selected))
							{
								world->upgradeTurret(world->selected);
								break;
							}
						}
						else if (ent->getType() == BT_Area) // Purchase area
						{
							// Create menu, or something
						}
						else // purchase SS
						{
							// Create menu, or something
						}
					}
				}
			}
		}

		world->selected = clicked;

		if (action == GLFW_RELEASE)
		{
			world->selected = nullptr;
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

	BaseEnemy enemy(Point(200, 200), renderController.get("Cute-Enemy-Coral-0.png"), 100, 100, 5, 5, 4);

	glfwSetMouseButtonCallback(win, OnMouseButton);
	Point p(100.0f, 100.0f);
	StraightTurret * turret = new StraightTurret(p, 32.0, 32.0, 5, 5, 5.0, 5, list<string> {"test"});
	world->addTower(turret);

	while (!glfwWindowShouldClose(win)) {
		//Update code here

		//Render code here
		glClear(GL_COLOR_BUFFER_BIT);
		//Draw all objects
		for (list<BaseEnemy*>::const_iterator itr = world->getEnemies()->cbegin(); itr != world->getEnemies()->cend(); itr++) {
			renderController.draw(*itr);
		}

		for (const auto& ent : *world->getTowers())
		{
			renderController.draw(ent);
		}

		renderController.draw(&enemy);

		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	return 0;
}