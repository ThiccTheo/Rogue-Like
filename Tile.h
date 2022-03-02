#pragma once
#include "Common.h"
#include "Player.h"
#include "Skeleton.h"
#include "ResourceManager.h"

class Player;

class Tile {
public:
	Sprite sprite;
	Tile(RenderWindow* window, vector<Tile>* tileVector, vector<Skeleton>* skeletonVector);
	void draw();
	void createLevelPathing(Player* player);
private:
	Tile(float& x, float& y);
	void initTiles(int& levelPosX, int& levelPosY, const Image& image);
	Image getRoomTemplate(int& templateType);
	vector<Tile>* tileVector = nullptr;
	vector<Skeleton>* skeletonVector = nullptr;
	RenderWindow* window = nullptr;
	Player* player = nullptr;
	const float POSITION_SCALAR, SPRITE_SIZE;
	const int START_TILE, DOWN_TILE, UP_TILE, UP_AND_DOWN_TILE, DOOR_TILE;
};
