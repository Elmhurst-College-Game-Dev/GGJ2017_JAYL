
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
#include "MusicWrapper.h"
#include <time.h>

#define MILLISECONDS_PER_FRAME 33

using namespace std;

#include "World.h"
World* world;
RenderControl renderController;
MusicWrapper music;

void OnMouseButton(GLFWwindow* win, int button, int action, int mods)
{
	cout << "Start Button!" << endl;
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		double x, y;
		glfwGetCursorPos(win, &x, &y);

		cout << "click at " << x << " " << y << endl;

		BaseTurret * clicked = nullptr;

		cout << "About to go through turrets!" << endl;

		for (auto ent : *(world->getTowers()))
		{
			Point clickSpot(static_cast<float>(x), static_cast<float>(y));

			Point entMiddle = ent->getMiddle();

			Point topLeft = Point(entMiddle.x - (ent->getWidth() / 2.0), entMiddle.y + (ent->getHeight() / 2.0));
			Point bottomRight = Point((entMiddle.x + (ent->getWidth() / 2.0)), (entMiddle.y - (ent->getHeight() / 2.0)));

			if (clickSpot.inBox(topLeft, bottomRight))
			{
				clicked = ent;
			}
		}
		cout << "Went through turrets!" << endl;
		if (clicked == nullptr)
		{
			cout << "About to go through buttons!" << endl;
			for (auto button = world->getButtons()->cbegin(); button != world->getButtons()->cend();button++)
			{
				cout << "itr " << *button << endl;
				ButtonObject* ent = *button;
				Point middle = ent->getMiddle();
				Point topLeft = Point(middle.x - (ent->getWidth() / 2.0), middle.y + (ent->getHeight() / 2.0));
				Point bottomRight = Point(middle.x + (ent->getWidth() / 2.0), middle.y - (ent->getHeight() / 2.0));
				
				if (middle.inBox(topLeft, bottomRight)) // clicked inside button
				{
					if (action == GLFW_RELEASE) // releasing m1 inside button
					{
						if (world->selected != nullptr)
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
				cout << "did buttons!" << endl;
			}
		}

		world->selected = clicked;

		if (action == GLFW_RELEASE)
		{
			world->selected = nullptr;
		}
	}
	cout << "Didnt crash!" << endl;
}

void OnGetCursorPos(GLFWwindow* win, double x, double y)
{
	if (world->purchasing != nullptr)
	{
		world->purchasing->setMiddle(Point(x, y));
	}
	else
	{
		for (auto ent : *(world->getButtons()))
		{
			Point curPose(x, y);

			Point entMiddle = ent->getMiddle();

			Point topLeft = Point(entMiddle.x - (ent->getWidth() / 2.0), entMiddle.y + (ent->getHeight() / 2.0));
			Point bottomRight = Point(entMiddle.x + (ent->getWidth() / 2.0), entMiddle.y - (ent->getHeight() / 2.0));

			if (curPose.inBox(topLeft, bottomRight))
			{
				ent->isHovered = true;
			}
			else
			{
				ent->isHovered = false;
			}
		}
	}
}

int main() {
	//music.add("ericsSong.mp3", "test");
	//music.play("test");

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
	Sprite spr = renderController.get("boom_27.png");
	BaseEnemy enemy(Point(200.0 , 200.0), spr, 100, 100, 5, 5, 4);

	glfwSetMouseButtonCallback(win, OnMouseButton);
	glfwSetCursorPosCallback(win, OnGetCursorPos);

	Point p(100.0f, 100.0f);
	StraightTurret * turret = new StraightTurret(p, 32.0, 32.0, 5, 5, 5.0, 5, list<string> {"CuteEnemyCoral-0.png"});
	world->addTower(turret);

	world->addButton(new ButtonObject(BT_Upgrade, Point(500.0, 500.0), renderController.get("CuteEnemyCoral-0.png"), renderController.get("CuteEnemyCoral-0.png"), 32.0, 32.0));
	world->iterate();
	while (!glfwWindowShouldClose(win)) {
		/*
		static clock_t lastThink = clock();
		cout << clock() - lastThink << endl;
		if (clock() - lastThink < 32)
		{
			world->think();
			lastThink = clock();
		}
		*/
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

		for (const auto& ent : *world->getButtons())
		{
			renderController.draw(ent);
		}

		renderController.draw(&enemy);

		glFlush();

		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	return 0;
}