#include "Skeleton.h"

vector<Skeleton> Skeleton::sv;

Skeleton::Skeleton(RenderWindow* window, vector<Skeleton>* skeletonVector) 
	:SPRITE_SIZE(16.f), HITBOX_THICKNESS(1.f),
	GRAVITY(0.025), TERMINAL_VELOCITY(0.f, 1.5f),
	TILE_SIZE(16.f)
{
	this->window = window;
	this->skeletonVector = skeletonVector;
}

Skeleton::Skeleton(float& x, float& y)
	:SPRITE_SIZE(16.f), HITBOX_THICKNESS(1.f),
	GRAVITY(0.025), TERMINAL_VELOCITY(0.f, 1.5f),
	TILE_SIZE(24.f)
{
	this->sprite.setTexture(ResourceManager::skeletonTexture);
	this->sprite.setPosition(x, y);
	this->topHitbox.setSize(Vector2f(SPRITE_SIZE - 2, HITBOX_THICKNESS));
	this->bottomHitbox.setSize(Vector2f(SPRITE_SIZE - 2, HITBOX_THICKNESS));
	this->topHitbox.setFillColor(Color::Red);
	this->bottomHitbox.setFillColor(Color::Red);
	this->topHitbox.setPosition(sprite.getPosition().x + 1, sprite.getPosition().y - 1);
	this->bottomHitbox.setPosition(sprite.getPosition().x + 1, sprite.getPosition().y + SPRITE_SIZE);
	this->sprite.setOrigin(SPRITE_SIZE / 2, 0.f);
	this->topHitbox.setOrigin(SPRITE_SIZE / 2, 0.f);
	this->bottomHitbox.setOrigin(SPRITE_SIZE / 2, 0.f);
}


void Skeleton::draw(){
	for (int i = 0; i < skeletonVector->size(); i++) {
		window->draw(skeletonVector->at(i).bottomHitbox);
		window->draw(skeletonVector->at(i).topHitbox);
		window->draw(skeletonVector->at(i).sprite);
	}
}

void Skeleton::update(){
	//skeletonVector->at(i).sprite

	for (int i = 0; i < skeletonVector->size(); i++) {
		skeletonVector->at(i).position = skeletonVector->at(i).sprite.getPosition();

		if (isBottomColliding() != nullptr) {
			skeletonVector->at(i).velocity.y = 0.f;
			skeletonVector->at(i).position.y = isBottomColliding()->sprite.getPosition().y - SPRITE_SIZE;
		}
		else if (isTopColliding() != nullptr) {
			skeletonVector->at(i).velocity.y = 0.f;
			skeletonVector->at(i).position.y = isTopColliding()->sprite.getPosition().y + TILE_SIZE + 1;
		}
		else {
			if (skeletonVector->at(i).velocity.y < TERMINAL_VELOCITY.y) {
				skeletonVector->at(i).velocity.y += GRAVITY;
			}
			else {
				skeletonVector->at(i).velocity.y = TERMINAL_VELOCITY.y;
			}
			skeletonVector->at(i).position.y += skeletonVector->at(i).velocity.y;
		}


		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		skeletonVector->at(i).sprite.setPosition(skeletonVector->at(i).position);
		skeletonVector->at(i).topHitbox.setPosition(skeletonVector->at(i).position.x + 1, skeletonVector->at(i).position.y - 1);
		skeletonVector->at(i).bottomHitbox.setPosition(skeletonVector->at(i).position.x + 1, skeletonVector->at(i).position.y + 16.f);
	}
}

void Skeleton::getTileVector(vector<Tile>* tileVector) {
	this->tileVector = tileVector;
}


Tile* Skeleton::isSideColliding() {
	Tile* collider = nullptr;
	for (int i = 0; i < tileVector->size(); i++) {
		for (int j = 0; j < skeletonVector->size(); j++) {
			if (skeletonVector->at(j).sprite.getGlobalBounds().intersects(tileVector->at(i).sprite.getGlobalBounds())) {
				collider = &tileVector->at(i);
				return collider;
			}
		}
	}
	return collider;
}

Tile* Skeleton::isTopColliding() {
	Tile* collider = nullptr;
	for (int i = 0; i < tileVector->size(); i++) {
		for (int j = 0; j < skeletonVector->size(); j++) {
			if (skeletonVector->at(j).topHitbox.getGlobalBounds().intersects(tileVector->at(i).sprite.getGlobalBounds())) {
				collider = &tileVector->at(i);
				return collider;
			}
		}
	}
	return collider;
}

Tile* Skeleton::isBottomColliding() {
	Tile* collider = nullptr;
	for (int i = 0; i < tileVector->size(); i++) {
		for (int j = 0; j < skeletonVector->size(); j++) {
			if (skeletonVector->at(j).bottomHitbox.getGlobalBounds().intersects(tileVector->at(i).sprite.getGlobalBounds())) {
				collider = &tileVector->at(i);
				return collider;
			}
		}
	}
	return collider;
}