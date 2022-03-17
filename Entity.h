#pragma once
#include "Common.h"
#include "Tile.h"

class Entity {
public:
	Tile *isSideColliding(bool isSolid, string&& type);
	Tile* isTopColliding(bool isSolid, string&& type);
	Tile* isBottomColliding(bool isSolid, string&& type);

	Sprite sprite;
	RectangleShape topHitbox, bottomHitbox;
};