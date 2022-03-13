#pragma once
#include "Common.h"
#include "Tile.h"
#include "ResourceManager.h"
#include "Game.h"

class Tile;

class Player {
public:
	static int health;
	static Sprite sprite;
	static void init();
	static void draw();
	static void update();
	static int jumpCounter;
	static bool showIFrames;
	static int iFrameCounter;
	static int iFrameCycles;
	static const int iFrameCycleNumber;
	static const int iFrameNumber;
	static float speed;
	static int xp;
	static const Vector2f TERMINAL_VELOCITY;
private:
	static const int XP_LIMIT;
	static Tile* isSideColliding(bool isSolid, string&& type);
	static Tile* isTopColliding(bool isSolid, string&& type);
	static Tile* isBottomColliding(bool isSolid, string&& type);
	static Vector2f velocity, position;
	static const float GRAVITY;
	static const float SPRITE_SIZE, HITBOX_THICKNESS;
	static RectangleShape topHitbox, bottomHitbox;
	static string animationType;
	static Clock animationClock;
	static void walkAnimation();
	static int walkFrame;
};