#pragma once
#include "Common.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Player.h"

class Chest {
public:
	Chest(float& x, float& y);
	static void UAD();
	static vector<Chest> chestVector;
private:
	Sprite sprite;
	bool isOpen;
};