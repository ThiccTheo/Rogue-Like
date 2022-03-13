#pragma once
#include "Common.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Player.h"

class Sword {
public:
	static Sprite sprite;
	static void init();
	static void draw();
	static void update();
	static int clickCounter;
	static bool showSword;
	static float clickDelay;
	static int attackFrame;
	static int damage;
	static const int MAX_DAMAGE;
private:
	static Clock animationClock;
	static void attackAnimation();

};