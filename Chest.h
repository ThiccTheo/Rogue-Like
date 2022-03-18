#pragma once
#include "Common.h"

class Chest {
public:
	Chest(float& x, float& y);
	static void draw();
	static vector<Chest> chestVector;
private:
	Sprite sprite;
	bool isOpen;
	void dropLoot();
};