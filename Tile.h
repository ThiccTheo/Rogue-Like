#pragma once
#include "Common.h"
#include "Player.h"

class Player;

class Tile {
public:
	Sprite sprite;
	Tile(RenderWindow* window, vector<Tile>* tileVector);
	void draw();
	void createLevelPathing(Player* player);
private:
	Tile(float& x, float& y, Texture* texture);
	void initTiles(int& levelPosX, int& levelPosY, Image* image);
	Image getRoomTemplate(int& templateType);
	vector<Tile>* tileVector = nullptr;
	RenderWindow* window = nullptr;
	Player* player = nullptr;
	Texture texture;
	const string SRC;
	const float POSITION_SCALAR = 16.f;
	const int START_TILE = 1, DOWN_TILE = 2, UP_TILE = 3, UP_AND_DOWN_TILE = 4, DOOR_TILE = 5;
	int x = 0, y = 0;
};
