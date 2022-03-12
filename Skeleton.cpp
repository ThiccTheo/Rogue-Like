#include "Skeleton.h"

const float Skeleton::SPRITE_SIZE = 16.f, Skeleton::HITBOX_THICKNESS = 1.f;
const float Skeleton::GRAVITY = 0.025f;
const Vector2f Skeleton::TERMINAL_VELOCITY = Vector2f(0.f, 1.5f);

vector<Skeleton> Skeleton::skeletonVector;

Skeleton::Skeleton(float& x, float& y){
	this->dir = 'R';
	this->sprite.setTexture(ResourceManager::skeletonTexture);
	this->sprite.setTextureRect(IntRect(0, 0, 16, 16));
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
	this->walkFrame = 0;
}

void Skeleton::draw(){
	for (size_t i = 0; i < skeletonVector.size(); i++) {
		if (skeletonVector[i].sprite.getGlobalBounds().intersects(Game::cullingPoint.getGlobalBounds())) {
			if (skeletonVector[i].animationType == "idle") {
				skeletonVector[i].sprite.setTextureRect(IntRect(0, 0, 16, 16));
			}
			else if (skeletonVector[i].animationType == "walk") {
				skeletonVector[i].walkAnimation();
			}
			Game::window.draw(skeletonVector[i].sprite);
		}
	}
}

void Skeleton::update(){
	Tile* tileCollider = nullptr;

	for (size_t i = 0; i < skeletonVector.size(); i++) {
		skeletonVector[i].position = skeletonVector[i].sprite.getPosition();

		tileCollider = skeletonVector[i].isBottomColliding(true, "");
		if (tileCollider != nullptr) {
			skeletonVector[i].velocity.y = 0.f;
			skeletonVector[i].position.y = tileCollider->sprite.getPosition().y - SPRITE_SIZE;
			tileCollider = skeletonVector[i].isTopColliding(true, "");
		}
		else if (tileCollider != nullptr) {
			skeletonVector[i].velocity.y = 0.1f;
			skeletonVector[i].position.y = tileCollider->sprite.getPosition().y + tileCollider->spriteDimensions.y + 1;
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
			skeletonVector[i].velocity.x = 1.0f;
		}
		else if (skeletonVector[i].dir == 'L') {
			skeletonVector[i].sprite.setScale(-1.f, 1.f);
			skeletonVector[i].velocity.x = -1.0f;
		}

		skeletonVector[i].position.x += skeletonVector[i].velocity.x;

		tileCollider = skeletonVector[i].isSideColliding(true, "");
		if (tileCollider != nullptr) {
			if (skeletonVector[i].dir == 'R') {
				skeletonVector[i].dir = 'L';
				skeletonVector[i].position.x = tileCollider->sprite.getPosition().x - ((SPRITE_SIZE/2) + (tileCollider->spriteDimensions.x /2));
			}
			else if (skeletonVector[i].dir == 'L') {
				skeletonVector[i].dir = 'R';
				skeletonVector[i].position.x = tileCollider->sprite.getPosition().x + ((SPRITE_SIZE / 2) + (tileCollider->spriteDimensions.x / 2));
			}
		}

		if (skeletonVector[i].velocity.y != 0) {
			skeletonVector[i].animationType = "idle";
		}
		else {
			skeletonVector[i].animationType = "walk";
		}

		skeletonVector[i].sprite.setPosition(skeletonVector[i].position);
		skeletonVector[i].topHitbox.setPosition(skeletonVector[i].position.x + 1, skeletonVector[i].position.y - 1);
		skeletonVector[i].bottomHitbox.setPosition(skeletonVector[i].position.x + 1, skeletonVector[i].position.y + 16.f);

		if (skeletonVector[i].sprite.getGlobalBounds().intersects(Player::sprite.getGlobalBounds()) && Player::showIFrames == false) {
			Player::health--;
			Player::showIFrames = true;
		}
	}
}

Tile* Skeleton::isSideColliding(bool isSolid, string&& type) {
	Tile* collider = nullptr;
	for (size_t i = 0; i < Tile::tileVector.size(); i++) {
		if(sprite.getGlobalBounds().intersects(Tile::tileVector[i].sprite.getGlobalBounds()) && Tile::tileVector[i].isSolid == isSolid){
			if (type != "" && type == Tile::tileVector[i].type) {
				collider = &Tile::tileVector[i];
				return collider;
			}
			else if (type == "") {
				collider = &Tile::tileVector[i];
				return collider;
			}
		}
	}
	return collider;
}

Tile* Skeleton::isTopColliding(bool isSolid, string&& type) {
	Tile* collider = nullptr;
	for (size_t i = 0; i < Tile::tileVector.size(); i++) {
		if (topHitbox.getGlobalBounds().intersects(Tile::tileVector[i].sprite.getGlobalBounds()) && Tile::tileVector[i].isSolid == isSolid) {
			if (type != "" && type == Tile::tileVector[i].type) {
				collider = &Tile::tileVector[i];
				return collider;
			}
			else if (type == "") {
				collider = &Tile::tileVector[i];
				return collider;
			}
		}
	}
	return collider;
}

Tile* Skeleton::isBottomColliding(bool isSolid, string&& type) {
	Tile* collider = nullptr;
	for (size_t i = 0; i < Tile::tileVector.size(); i++) {
		if (bottomHitbox.getGlobalBounds().intersects(Tile::tileVector[i].sprite.getGlobalBounds()) && Tile::tileVector[i].isSolid == isSolid) {
			if (type != "" && type == Tile::tileVector[i].type) {
				collider = &Tile::tileVector[i];
				return collider;
			}
			else if (type == "") {
				collider = &Tile::tileVector[i];
				return collider;
			}
		}
	}
	return collider;
}

void Skeleton::walkAnimation() {
	if (walkFrame == 0) {
		sprite.setTextureRect(IntRect(16, 0, 16, 16));
	}

	else if (walkFrame == 1) {
		sprite.setTextureRect(IntRect(32, 0, 16, 16));
	}

	if (animationClock.getElapsedTime().asSeconds() > 0.15) {
		walkFrame++;
		if (walkFrame > 1) {
			walkFrame = 0;
		}
		animationClock.restart();
	}
}