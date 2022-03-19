#pragma once
#include "Common.h"

class Tile;

class Entity {
public:
	Tile* isSideColliding(bool isSolid, string&& type);
	Tile* isTopColliding(bool isSolid, string&& type);
	Tile* isBottomColliding(bool isSolid, string&& type);
	Vector2f position, velocity;
	Sprite sprite;
	float dir;
	RectangleShape topHitbox, bottomHitbox;
};