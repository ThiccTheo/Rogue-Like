#pragma once
#include "Common.h"
#include "ResourceManager.h"
#include "Tile.h"
#include "Game.h"
#include "Sword.h"

class Tile;

class Skeleton {
public:
	Skeleton(float& x, float& y);
	static void draw();
	static void update();
	Sprite sprite;
	static vector<Skeleton> skeletonVector;
private:
	string animationType;
	static const float SPRITE_SIZE, HITBOX_THICKNESS, GRAVITY;
	static const Vector2f TERMINAL_VELOCITY;
	Vector2f position, velocity;
	Tile* collidingTile = nullptr;
	char dir;
	RectangleShape topHitbox, bottomHitbox;
	Tile* isSideColliding(bool isSolid, string&& type);
	Tile* isTopColliding(bool isSolid, string&& type);
	Tile* isBottomColliding(bool isSolid, string&& type);
	void walkAnimation();
	Clock animationClock;
	int walkFrame;
};