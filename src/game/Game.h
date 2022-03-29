#pragma once
#include "../../vendor/Vendor.h"
#include "Common.h"

class Game {
public:
	static RenderWindow window;
	static View view;
	static RectangleShape cullingPoint;
	static void setup();
	static void loadLevel();
	static void run();
	static const float WIDTH;
	static const float HEIGHT;
	static int currentLevel;
private:
};