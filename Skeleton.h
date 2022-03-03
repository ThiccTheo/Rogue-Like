#pragma once
#include "Common.h"
#include "ResourceManager.h"
#include "Tile.h"

class Tile;

class Skeleton {
public:
	Skeleton(RenderWindow* window, vector<Skeleton> *skeletonVector);
	Skeleton(float& x, float& y);
	void draw();
	void update();
	Sprite sprite;
	void getTileVector(vector<Tile>* tileVector);
	static vector<Skeleton> sv;
private:
	RenderWindow* window = nullptr;
	vector<Skeleton>* skeletonVector = nullptr;
	vector<Tile>* tileVector = nullptr;
	const float SPRITE_SIZE, HITBOX_THICKNESS, TILE_SIZE;
	const float GRAVITY;
	const Vector2f TERMINAL_VELOCITY;
	Vector2f position, velocity;
	RectangleShape topHitbox, bottomHitbox;
	Tile* isSideColliding();
	Tile* isTopColliding();
	Tile* isBottomColliding();
};