#include "Enemy.h"

Skeleton::Skeleton(RenderWindow* window, vector<Skeleton>* skeletonVector, string src) 
	:SPRITE_SIZE(16.f)
{
	texture.loadFromFile(src);
	this->window = window;
	this->skeletonVector = skeletonVector;
}

Skeleton::Skeleton(float x, float y)
	:SPRITE_SIZE(16.f)
{
	this->sprite.setTexture(texture);
	this->sprite.setOrigin(SPRITE_SIZE / 2, 0.f);
	this->sprite.setPosition(x, y);
}

void Skeleton::draw(){
	for (int i = 0; i < skeletonVector->size(); i++) {
		window->draw(skeletonVector->at(i).sprite);
	}
}

void Skeleton::update()
{
}
