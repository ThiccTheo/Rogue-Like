#include "Skeleton.h"
#include "../../resource/ResourceManager.h"
#include "../../tile/Tile.h"
#include "../../game/Game.h"
#include "../../weapon/sword/Sword.h"
#include "../../player/Player.h"

const float Skeleton::SPRITE_SIZE = 16.f, Skeleton::HITBOX_THICKNESS = 1.f;
const float Skeleton::GRAVITY = 0.025f;
const Vector2f Skeleton::TERMINAL_VELOCITY = Vector2f(0.f, 1.5f);

vector<Skeleton> Skeleton::skeletonVector;

Skeleton::Skeleton(float& x, float& y) {
	this->dir = 1.f;
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
	this->animationFrame = 0;
}

void Skeleton::draw() {
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

void Skeleton::update() {
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

		skeletonVector[i].sprite.setScale(skeletonVector[i].dir, 1.f);
		skeletonVector[i].velocity.x = 1.0f * skeletonVector[i].dir;

		skeletonVector[i].position.x += skeletonVector[i].velocity.x;

		tileCollider = skeletonVector[i].isSideColliding(true, "");
		if (tileCollider != nullptr) {
			if (skeletonVector[i].dir == 1.f) {
				skeletonVector[i].dir = -1.f;
				skeletonVector[i].position.x = tileCollider->sprite.getPosition().x - ((SPRITE_SIZE / 2) + (tileCollider->spriteDimensions.x / 2));
			}
			else if (skeletonVector[i].dir == -1.f) {
				skeletonVector[i].dir = 1.f;
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

		if (Sword::showSword == true && Sword::sprite.getGlobalBounds().intersects(skeletonVector[i].sprite.getGlobalBounds())) {
			skeletonVector.erase(skeletonVector.begin() + i);
			Player::xp++;
		}
		else if (Player::bottomHitbox.getGlobalBounds().intersects(skeletonVector[i].topHitbox.getGlobalBounds()) && Player::velocity.y > 0){
			skeletonVector.erase(skeletonVector.begin() + i);
			Player::animationType = "jump";
			Player::velocity.y = -1.f;
			Player::xp++;
		}
	}
}

void Skeleton::walkAnimation() {
	if (animationFrame == 0) {
		sprite.setTextureRect(IntRect(16, 0, 16, 16));
	}

	else if (animationFrame == 1) {
		sprite.setTextureRect(IntRect(32, 0, 16, 16));
	}

	if (animationClock.getElapsedTime().asSeconds() > 0.15) {
		animationFrame++;
		if (animationFrame > 1) {
			animationFrame = 0;
		}
		animationClock.restart();
	}
}