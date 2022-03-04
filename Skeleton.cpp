#include "Skeleton.h"

const float Skeleton::SPRITE_SIZE = 16.f, Skeleton::HITBOX_THICKNESS = 1.f, Skeleton::TILE_SIZE = 24.f;
const float Skeleton::GRAVITY = 0.025;
const Vector2f Skeleton::TERMINAL_VELOCITY = Vector2f(0.f, 1.5f);

vector<Skeleton> Skeleton::skeletonVector;

Skeleton::Skeleton(float& x, float& y){
	this->dir = 'R';
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
	for (int i = 0; i < skeletonVector.size(); i++) {
		if (skeletonVector[i].sprite.getGlobalBounds().intersects(Game::cullingPoint.getGlobalBounds())) {
			//Game::window.draw(skeletonVector[i].bottomHitbox);
			//Game::window.draw(skeletonVector[i].topHitbox);
			Game::window.draw(skeletonVector[i].sprite);
		}
	}
}

void Skeleton::update(){
	Skeleton* skeletonPtr = nullptr;
	for (int i = 0; i < skeletonVector.size(); i++) {
		skeletonVector[i].position = skeletonVector[i].sprite.getPosition();

		skeletonPtr = isBottomColliding();
		if (skeletonPtr != nullptr) {
			skeletonPtr->velocity.y = 0.f;
			skeletonPtr->position.y = skeletonPtr->collidingTile->sprite.getPosition().y - SPRITE_SIZE;
			skeletonPtr = isTopColliding();
		}
		else if (skeletonPtr != nullptr) {
			skeletonPtr->velocity.y = 0.f;
			skeletonPtr->position.y = skeletonPtr->collidingTile->sprite.getPosition().y + TILE_SIZE + 1;
		}
		else {
			if (skeletonVector[i].velocity.y < TERMINAL_VELOCITY.y) {
				skeletonVector[i].velocity.y += GRAVITY;
			}
			else {
				skeletonVector[i].velocity.y = TERMINAL_VELOCITY.y;
			}
			skeletonVector[i].position.y += skeletonVector[i].velocity.y;
		}

		if (skeletonVector[i].dir == 'R') {
			skeletonVector[i].sprite.setScale(1.f, 1.f);
			skeletonVector[i].velocity.x = 0.1f;
		}
		else if (skeletonVector[i].dir == 'L') {
			skeletonVector[i].sprite.setScale(-1.f, 1.f);
			skeletonVector[i].velocity.x = -0.1f;
		}

		skeletonPtr = isSideColliding();
		if (skeletonPtr != nullptr) {
			skeletonPtr->velocity.x *= -1.f;
			if (skeletonPtr->dir == 'R') {
				skeletonPtr->dir = 'L';
			}
			else if (skeletonPtr->dir == 'L') {
				skeletonPtr->dir = 'R';
			}
		}

		skeletonPtr = nullptr;
		skeletonVector[i].position.x += skeletonVector[i].velocity.x;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		skeletonVector[i].sprite.setPosition(skeletonVector[i].position);
		skeletonVector[i].topHitbox.setPosition(skeletonVector[i].position.x + 1, skeletonVector[i].position.y - 1);
		skeletonVector[i].bottomHitbox.setPosition(skeletonVector[i].position.x + 1, skeletonVector[i].position.y + 16.f);
	}
}

Skeleton* Skeleton::isSideColliding() {
	Skeleton* collider = nullptr;
	for (int i = 0; i < Tile::tileVector.size(); i++) {
		for (int j = 0; j < skeletonVector.size(); j++) {
			if (skeletonVector[j].sprite.getGlobalBounds().intersects(Tile::tileVector[i].sprite.getGlobalBounds())) {
				skeletonVector[j].collidingTile = &Tile::tileVector[i];
				collider = &skeletonVector[j];
				return collider;
			}
			else {
				skeletonVector[j].collidingTile = nullptr;
			}
		}
	}
	return collider;
}

Skeleton* Skeleton::isTopColliding() {
	Skeleton* collider = nullptr;
	for (int i = 0; i < Tile::tileVector.size(); i++) {
		for (int j = 0; j < skeletonVector.size(); j++) {
			if (skeletonVector[j].topHitbox.getGlobalBounds().intersects(Tile::tileVector[i].sprite.getGlobalBounds())) {
				skeletonVector[j].collidingTile = &Tile::tileVector[i];
				collider = &skeletonVector[j];
				return collider;
			}
			else {
				skeletonVector[j].collidingTile = nullptr;
			}
		}
	}
	return collider;
}

Skeleton* Skeleton::isBottomColliding() {
	Skeleton* collider = nullptr;
	for (int i = 0; i < Tile::tileVector.size(); i++) {
		for (int j = 0; j < skeletonVector.size(); j++) {
			if (skeletonVector[j].bottomHitbox.getGlobalBounds().intersects(Tile::tileVector[i].sprite.getGlobalBounds())) {
				skeletonVector[j].collidingTile = &Tile::tileVector[i];
				collider = &skeletonVector[j];
				return collider;
			}
			else {
				skeletonVector[j].collidingTile = nullptr;
			}
		}
	}
	return collider;
}