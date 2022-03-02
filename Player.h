#pragma once
#include "Common.h"
#include "Tile.h"
#include "ResourceManager.h"

class Tile;

class Player {
public:
	Player(RenderWindow* window, View* view, vector<Tile>* tileVector);
	Sprite sprite;
	void draw();
	void update();
	int jumpCounter;
private:
	vector<Tile>* tileVector = nullptr;
	View* view = nullptr;
	RenderWindow* window = nullptr;
	Tile* isSideColliding();
	Tile* isTopColliding();
	Tile* isBottomColliding();
	Vector2f velocity, position;
	const float GRAVITY;
	const Vector2f TERMINAL_VELOCITY;
	const float SPRITE_SIZE, HITBOX_THICKNESS, TILE_SIZE;
	RectangleShape topHitbox, bottomHitbox;
};