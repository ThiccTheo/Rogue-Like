#pragma once
#include "../../../vendor/Vendor.h"
#include "../../game/Common.h"
#include "../Entity.h"

class Skeleton: public Entity{
public:
	Skeleton(float& x, float& y);
	static void draw();
	static void update();
	static vector<Skeleton> skeletonVector;
private:
	string animationType;
	static const float SPRITE_SIZE, HITBOX_THICKNESS, GRAVITY;
	static const Vector2f TERMINAL_VELOCITY;
	void walkAnimation();
	Clock animationClock;
	int animationFrame;
};