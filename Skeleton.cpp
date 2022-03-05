#include "Skeleton.h"

const float Skeleton::SPRITE_SIZE = 16.f, Skeleton::HITBOX_THICKNESS = 1.f;
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
	Tile* tilePtr = nullptr;
	for (int i = 0; i < skeletonVector.size(); i++) {
		skeletonVector[i].position = skeletonVector[i].sprite.getPosition();

		if (skeletonVector[i].isBottomColliding() != nullptr) {
			skeletonVector[i].velocity.y = 0.f;
			skeletonVector[i].position.y = skeletonVector[i].isBottomColliding()->sprite.getPosition().y - SPRITE_SIZE;
		}
		else if (skeletonVector[i].isTopColliding() != nullptr) {
			skeletonVector[i].velocity.y = 0.1f;
			skeletonVector[i].position.y = skeletonVector[i].isTopColliding()->sprite.getPosition().y + Tile::SPRITE_SIZE + 1;
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
			skeletonVector[i].velocity.x = 0.5f;
		}
		else if (skeletonVector[i].dir == 'L') {
			skeletonVector[i].sprite.setScale(-1.f, 1.f);
			skeletonVector[i].velocity.x = -0.5f;
		}

		skeletonVector[i].position.x += skeletonVector[i].velocity.x;

		tilePtr = skeletonVector[i].isSideColliding();
		if (tilePtr != nullptr) {
			if (skeletonVector[i].dir == 'R') {
				skeletonVector[i].dir = 'L';
				skeletonVector[i].position.x = tilePtr->sprite.getPosition().x - ((SPRITE_SIZE/2) + (Tile::SPRITE_SIZE/2));
			}
			else if (skeletonVector[i].dir == 'L') {
				skeletonVector[i].dir = 'R';
				skeletonVector[i].position.x = tilePtr->sprite.getPosition().x + ((SPRITE_SIZE / 2) + (Tile::SPRITE_SIZE / 2));
			}
		}

		skeletonVector[i].sprite.setPosition(skeletonVector[i].position);
		skeletonVector[i].topHitbox.setPosition(skeletonVector[i].position.x + 1, skeletonVector[i].position.y - 1);
		skeletonVector[i].bottomHitbox.setPosition(skeletonVector[i].position.x + 1, skeletonVector[i].position.y + 16.f);
	}
}

Tile* Skeleton::isSideColliding() {
	Tile* collider = nullptr;
	for (int i = 0; i < Tile::tileVector.size(); i++) {
		if(sprite.getGlobalBounds().intersects(Tile::tileVector[i].sprite.getGlobalBounds())){
			collider = &Tile::tileVector[i];
			return collider;
		}
	}
	return collider;
}

Tile* Skeleton::isTopColliding() {
	Tile* collider = nullptr;
	for (int i = 0; i < Tile::tileVector.size(); i++) {
		if (topHitbox.getGlobalBounds().intersects(Tile::tileVector[i].sprite.getGlobalBounds())) {
			collider = &Tile::tileVector[i];
			return collider;
		}
	}
	return collider;
}

Tile* Skeleton::isBottomColliding() {
	Tile* collider = nullptr;
	for (int i = 0; i < Tile::tileVector.size(); i++) {
		if (bottomHitbox.getGlobalBounds().intersects(Tile::tileVector[i].sprite.getGlobalBounds())) {
			collider = &Tile::tileVector[i];
			return collider;
		}
	}
	return collider;
}