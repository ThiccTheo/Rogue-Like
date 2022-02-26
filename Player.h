#pragma once
#include "Common.h"
#include "Tile.h"

class Tile;

class Player {
public:
	Player(RenderWindow* window, string src, View* view, vector<Tile>* tileVector);
	Sprite sprite;
	void draw();
	void update();
private:
	vector<Tile>* tileVector = nullptr;
	Tile* isSideColliding();
	Tile* isTopColliding();
	Tile* isBottomColliding();
	View* view = nullptr;
	float* deltaTime = nullptr;
	RenderWindow* window = nullptr;
	Texture texture;
	Vector2f velocity, position;
	const float GRAVITY;
	const Vector2f TERMINAL_VELOCITY;
	const float SPRITE_SIZE, HITBOX_THICKNESS;
	RectangleShape topHitbox, bottomHitbox;
};