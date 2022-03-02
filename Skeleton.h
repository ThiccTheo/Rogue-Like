#pragma once
#include "Common.h"
#include "ResourceManager.h"

class Skeleton {
public:
	Skeleton(RenderWindow* window, vector<Skeleton> *skeletonVector);
	Skeleton(float& x, float& y);
	void draw();
	void update();
	Sprite sprite;
private:
	RenderWindow* window = nullptr;
	vector<Skeleton>* skeletonVector = nullptr;
	const float SPRITE_SIZE;
};