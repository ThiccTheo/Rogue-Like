#pragma once
#include "Common.h"
#include "Tile.h"
#include "ResourceManager.h"
#include "Game.h"

class Tile;

class Player {
public:
	static Sprite sprite;
	static void init();
	static void draw();
	static void update();
	static int jumpCounter;
private:
	static Tile* isSideColliding();
	static Tile* isTopColliding();
	static Tile* isBottomColliding();
	static Vector2f velocity, position;
	static const float GRAVITY;
	static const Vector2f TERMINAL_VELOCITY;
	static const float SPRITE_SIZE, HITBOX_THICKNESS;
	static RectangleShape topHitbox, bottomHitbox;
	static string animationType;
	static Clock animationClock;
	static void walkAnimation();
	static int walkFrame;
};