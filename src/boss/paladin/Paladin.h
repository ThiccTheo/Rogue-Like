#pragma once

#include "../../../vendor/Vendor.h"
#include "../../game/Common.h"

class Tile;

class Paladin {
public:
	static void init();
	static void draw();
	static void update();
	static Sprite sprite;
	static bool flag;
private:
	static Tile* isSideColliding(bool isSolid, string&& type);
	static float dir;
	static Vector2f velocity;
	static Vector2f position;
};