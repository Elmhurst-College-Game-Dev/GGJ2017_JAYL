
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
#include "AreaTurret.h"
#include <assert.h>
#include "NumberObject.h"
#include "WaveObject.h"
#include "MusicWrapper.h"
#include <time.h>

#define MILLISECONDS_PER_FRAME 33

using namespace std;

#include "World.h"
World* world;
RenderControl renderController;
MusicWrapper music;

const list<string> SS_SPRITES{ "top_radio" };
const list<string> AREA_SPRITES{ "top_radio" };

list<BaseObject*> drawThese;

void OnMouseButton(GLFWwindow* win, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		double x, y;
		glfwGetCursorPos(win, &x, &y);
		Point clickSpot(x, y);

		cout << "click at " << x << " " << y << endl;
	//	drawThese.push_back(new BaseObject(clickSpot, renderController.get("top_radio"), 32.0, 32.0));

		if (world->canPlaceTower(clickSpot))
		{
			cout << "You can place things here!" << endl;
		}
		else
		{
			cout << "You cant place things here!" << endl;
		}

		BaseTurret * clicked = nullptr;
		
		if (world->purchasing != nullptr) // Player is trying to place down a tower
		{
			if (world->canPlaceTower(clickSpot))
			{
				world->addTower(world->purchasing);
				world->subtractMoney(world->purchasing->getUpgradePrice());
				world->purchasing = nullptr;
			}
		}
		else
		{
			for (auto ent : *(world->getTowers())) // check if we've touched a tower
			{
				Point entMiddle = ent->getMiddle();

				Point topLeft = Point(entMiddle.x - (ent->getWidth() / 2.0), entMiddle.y - (ent->getHeight() / 2.0));
				Point bottomRight = Point((entMiddle.x + (ent->getWidth() / 2.0)), (entMiddle.y + (ent->getHeight() / 2.0)));

				if (clickSpot.inBox(topLeft, bottomRight))
				{
					clicked = ent;
				}
			}

			if (clicked == nullptr) // We didn't click on a tower.
			{
				for (auto button = world->getButtons()->cbegin(); button != world->getButtons()->cend(); button++)
				{
					ButtonObject* ent = *button;
					Point middle = ent->getMiddle();
					Point topLeft = Point(middle.x - (ent->getWidth() / 2.0), middle.y - (ent->getHeight() / 2.0));
					Point bottomRight = Point(middle.x + (ent->getWidth() / 2.0), middle.y + (ent->getHeight() / 2.0));

					if (clickSpot.inBox(topLeft, bottomRight)) // clicked inside button
					{
						if (world->selected != nullptr)
						{
							if (ent->getType() == BT_Upgrade && world->canUpgradeTurret(world->selected)) // Upgrade
							{
						//		cout << "About to upgrade" << endl;
								world->upgradeTurret(world->selected);
								break;
							}
						}
						else if (ent->getType() == BT_Area)
						{
						//	cout << "Clicked area" << endl;
							world->purchasing = new AreaTurret(clickSpot, 32.0f, 32.0f, 20, 15, 100000000.0, 100, AREA_SPRITES);
							break;
						}
						else if (ent->getType() == BT_SS)
						{
						//	cout << "Clicked SS" << endl;
							world->purchasing = new StraightTurret(clickSpot, 32.0, 32.0, 20, 15, 100000000.0, 100, SS_SPRITES);
							break;
						}
					}
				}
			}

			world->selected = clicked;
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

	
	if (!glfwInit()) {
		cout << "Could not init GLFW" << endl;
		return 1;
	}
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
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


	vector<string> sprites{ "CuteEnemyCoral", "CuteEnemyBall", "CuteEnemyStone", "CuteEnemySeaweed", "CuteEnemyFluff" };
	world = new World(sprites);

	//Point p(100.0f, 100.0f);
	//StraightTurret * turret = new StraightTurret(p, 32.0, 32.0, 5, 5, 5.0, 5, list<string> {"CuteEnemyCoral-0.png"});
	//world->addTower(turret);

	Sprite background_map = renderController.get("Map-0");

	world->addButton(new ButtonObject(BT_SS, Point(16.0f + 101.0f, 59.0f), renderController.get("BuyUnselected"), renderController.get("BuySelected"), 202.0f, 80.0f));
	BaseObject straightShotBuyIcon(Point(48.0f+16.0f, 43.0f + 16.0f), renderController.get("top_radio"), 32.0f, 32.0f);
	world->addButton(new ButtonObject(BT_Area, Point(221.0f + 101.0f, 59.0f), renderController.get("BuyUnselected"), renderController.get("BuySelected"), 202.0f, 80.0f));
	BaseObject areaBuyIcon(Point(253.0f+16.0f, 43.0f + 16.0f), renderController.get("top_radio"), 32.0f, 32.0f);
	world->addButton(new ButtonObject(BT_Upgrade, Point(425.0f + 101.0f, 59.0f), renderController.get("UpgradeUnselected"), renderController.get("UpgradeSelected"), 202.0f, 80.0f));

	//Wave object
	WaveObject wave(10, 30);

	//HEADS UP DISPLAY OBJECTS
	BaseObject hudBackground(Point(640.0f, 60.0f), renderController.get("HUD-0"), 1280, 120);
	BaseObject currencyBackground(Point(802.0f, 60.0f), renderController.get("HUD-Currency"), 308.0f, 100.0f);
	BaseObject enemyWaveBackground(Point(962.0f+154.0f, 60.0f), renderController.get("HUD-EnemyWave"), 308.0f, 100.0f);
	BaseObject enemyWaveIcon(Point(962.0f + 113.0f, 60.0f), renderController.get("CuteEnemyCoral-0"), 32.0f, 32.0f);
	NumberObject currencyNumber(Point(782.0f, 60.0f), 5, 100);
	NumberObject enemyWaveNumber(Point(177.0f + 962.0f, 60.0f), 2, 0);

	BaseEnemy* enemy = new BaseEnemy(wave.getMiddle(), renderController.get("top_radio"), 32.0f, 32.0f, 5, 5.0, 1);

	//cout << "Created!" << endl;

	while (!glfwWindowShouldClose(win)) {
		static clock_t lastThink = clock();
		//cout << clock() - lastThink << endl;
		if (clock() - lastThink > 32)
		{
			enemy->think();
			world->think();
			lastThink = clock();
		}
		wave.think();
		
		//Update HUD values
		currencyNumber.setValue(world->getMoney());
		enemyWaveNumber.setValue(world->getEnemiesLeft());

		//Render code here
		glClear(GL_COLOR_BUFFER_BIT);

		background_map.draw(0.0f, 1280.0f, 600.0f, 640.0f, 420.0f);

		//Draw all objects
		for (list<BaseEnemy*>::const_iterator itr = world->getEnemies()->cbegin(); itr != world->getEnemies()->cend(); itr++) {
			(*itr)->draw();
		}

		for (const auto& ent : *world->getTowers())
		{
			ent->draw();
		}

		for (const auto& ent : drawThese)
		{
			ent->draw();
		}

		wave.draw();

		if (world->purchasing != nullptr)
		{
			world->purchasing->draw();
		}

		//DRAW THE HEADS UP DISPLAY
		hudBackground.draw();
		currencyBackground.draw();
		enemyWaveBackground.draw();
		enemyWaveIcon.draw();
		currencyNumber.draw();
		enemyWaveNumber.draw();
		
		//Draw buttons after the HUD
		for (const auto& ent : *world->getButtons())
		{
			ent->draw();
		}

		//icons on top of buy buttons
		straightShotBuyIcon.draw();
		areaBuyIcon.draw();

		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	return 0;
}