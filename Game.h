#pragma once
#include "Common.h"
#include "Tile.h"
#include "Skeleton.h"
#include "Chest.h"

class Game {
public:
	static RenderWindow window;
	static View view;
	static RectangleShape cullingPoint;
	static void setup();
	static void loadLevel();
private:
	static const float WIDTH;
	static const float HEIGHT;
};