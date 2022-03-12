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
	static void setupBackground();
	static vector<Tile> tileVector;
	Vector2f spriteDimensions;
	bool isSolid;
	string type;
private:
	Tile(float& x, float& y, string&& type, bool isSolid);
	Tile(int& x, int& y, bool isSolid);
	static void initTiles(int& levelPosX, int& levelPosY, const Image& image);
	static Image getRoomTemplate(int& templateType);
	static const float POSITION_SCALAR, SCALE;
	static const int START_TILE, DOWN_TILE, UP_TILE, UP_AND_DOWN_TILE, DOOR_TILE;
};
