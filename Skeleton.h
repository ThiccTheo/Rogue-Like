#pragma once
#include "Common.h"

class Skeleton {
public:
	Skeleton(RenderWindow* window, vector<Skeleton> *skeletonVector, string src);
	Skeleton(float x, float y);
	void draw();
	void update();
private:
	Sprite sprite;
	Texture texture;
	RenderWindow* window = nullptr;
	vector<Skeleton>* skeletonVector = nullptr;
	const float SPRITE_SIZE;
};