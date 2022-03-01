#pragma once
#include "Common.h"

class Skeleton {
public:
	Skeleton(RenderWindow* window, vector<Skeleton> *skeletonVector);
	Skeleton(float& x, float& y);
	void draw();
	void update();
	Sprite sprite;
private:
	Texture texture;
	RenderWindow* window = nullptr;
	vector<Skeleton>* skeletonVector = nullptr;
	const float SPRITE_SIZE;
};