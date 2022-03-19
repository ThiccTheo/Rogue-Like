#pragma once
#include "Common.h"
#include "Entity.h"

class Slime: public Entity {
public:
	static vector<Slime> slimeVector;
	Slime(float& x, float& y);
	static void draw();
	static void update();
private:
	static const Vector2f SPRITE_DIMENSIONS;
	static const float GRAVITY;
	static const Vector2f TERMINAL_VELOCITY;
	int jumpDelay;
};