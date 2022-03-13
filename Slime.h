#pragma once
#include "Common.h"
#include "Game.h"
#include "Tile.h"
#include "ResourceManager.h"

class Slime {
public:
	static vector<Slime> slimeVector;
	Slime(float& x, float& y);
	static void draw();
	static void update();
private:
	static const Vector2f SPRITE_DIMENSIONS;
	char dir;
	Sprite sprite;
	RectangleShape topHitbox, bottomHitbox;
	Tile* isSideColliding(bool isSolid, string&& type);
	Tile* isTopColliding(bool isSolid, string&& type);
	Tile* isBottomColliding(bool isSolid, string&& type);
	static const float GRAVITY;
	static const Vector2f TERMINAL_VELOCITY;
	Vector2f position, velocity;
};