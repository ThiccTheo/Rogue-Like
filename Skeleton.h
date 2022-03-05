#pragma once
#include "Common.h"
#include "ResourceManager.h"
#include "Tile.h"
#include "Game.h"

class Tile;

class Skeleton {
public:
	Skeleton(float& x, float& y);
	static void draw();
	static void update();
	Sprite sprite;
	static vector<Skeleton> skeletonVector;
private:
	static const float SPRITE_SIZE, HITBOX_THICKNESS, GRAVITY;
	static const Vector2f TERMINAL_VELOCITY;
	Vector2f position, velocity;
	Tile* collidingTile = nullptr;
	char dir;
	RectangleShape topHitbox, bottomHitbox;
	Tile* isSideColliding();
	Tile* isTopColliding();
	Tile* isBottomColliding();
};