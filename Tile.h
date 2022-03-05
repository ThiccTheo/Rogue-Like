#pragma once
#include "Common.h"
#include "Player.h"
#include "Skeleton.h"
#include "ResourceManager.h"

class Player;

class Skeleton;

class Tile {
public:
	Sprite sprite;
	static void draw();
	static void createLevelPathing();
	static vector<Tile> tileVector;
	static const float SPRITE_SIZE;
private:
	Tile(float& x, float& y);
	static void initTiles(int& levelPosX, int& levelPosY, const Image& image);
	static Image getRoomTemplate(int& templateType);
	static const float POSITION_SCALAR, SCALE;
	static const int START_TILE, DOWN_TILE, UP_TILE, UP_AND_DOWN_TILE, DOOR_TILE;
};
