
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
#include "WaveObject.h"
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
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
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
			Point bottomRight = Point((entMiddle.x + (ent->getWidth() / 2.0)), (entMiddle.y - (ent->getHeight() / 2.0)));

			if (clickSpot.inBox(topLeft, bottomRight))
			{
				clicked = ent;
			}
		}
		if (clicked == nullptr)
		{
			for (auto button = world->getButtons()->cbegin(); button != world->getButtons()->cend();button++)
			{
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
			}
		}

		world->selected = clicked;

		if (action == GLFW_RELEASE)
		{
			world->selected = nullptr;
		}
	}
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

			Point topLeft = Point(entMiddle.x - (ent->getWidth() / 2.0), entMiddle.y +(ent->getHeight() / 2.0));
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
	music.add("ericsSong.mp3", "test");
	music.play("test");

	vector<string> sprites{ "Cute-Enemy-Coral-0.png", "sprite2", "sprite3", "sprite4", "sprite5" };
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
	glfwSetCursorPosCallback(win, OnGetCursorPos);

	//Point p(100.0f, 100.0f);
	//StraightTurret * turret = new StraightTurret(p, 32.0, 32.0, 5, 5, 5.0, 5, list<string> {"CuteEnemyCoral-0.png"});
	//world->addTower(turret);

	Sprite background_map = renderController.get("Map-0");

	//world->addButton(new ButtonObject(BT_Upgrade, Point(500.0, 500.0), renderController.get("CuteEnemyCoral-0.png"), renderController.get("CuteEnemyCoral-0.png"), 32.0, 32.0));
	//world->iterate();

	//Wave object
	WaveObject wave(10, 30);

	BaseEnemy* enemy = new BaseEnemy(wave.getMiddle(), renderController.get("CuteEnemyCoral-0"), 32.0f, 32.0f, 5, 5.0, 1);

	cout << "Created!" << endl;

	while (!glfwWindowShouldClose(win)) {
		/*
		static clock_t lastThink = clock();
		cout << clock() - lastThink << endl;
		if (clock() - lastThink > 32)
		{
			world->think();
			lastThink = clock();
		}
	*/
		static clock_t lastThink = clock();
		cout << clock() - lastThink << endl;
		if (clock() - lastThink > 32)
		{
			cout << "Thinking!" << endl;
			enemy->think();
			cout << "New position! " << enemy->getMiddle().x << " " << enemy->getMiddle().y << endl;
			lastThink = clock();
			Sleep(2000);
		}
		
		//Render code here
		glClear(GL_COLOR_BUFFER_BIT);
		wave.think();

		//Draw all objects
		for (list<BaseEnemy*>::const_iterator itr = world->getEnemies()->cbegin(); itr != world->getEnemies()->cend(); itr++) {
			(*itr)->draw();
		}

		for (const auto& ent : *world->getTowers())
		{
			ent->draw();
		}

		for (const auto& ent : *world->getButtons())
		{
			ent->draw();
		}

		background_map.draw(0.0f, 1280.0f, 600.0f, 640.0f, 420.0f);
		wave.draw();
		enemy->draw();

		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	return 0;
}