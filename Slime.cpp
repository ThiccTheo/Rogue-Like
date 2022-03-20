#include "Slime.h"
#include "Game.h"
#include "Tile.h"
#include "ResourceManager.h"
#include "Player.h"
#include "Sword.h"

vector<Slime> Slime::slimeVector;
const Vector2f Slime::SPRITE_DIMENSIONS = Vector2f(16.f, 11.f);

const float Slime::GRAVITY = 0.025f;
const Vector2f Slime::TERMINAL_VELOCITY = Vector2f(0.f, 1.5f);

Slime::Slime(float& x, float& y) {
	this->sprite.setTexture(ResourceManager::slimeTexture);
	this->sprite.setTextureRect(IntRect(0, 0, 16, 11));
	this->dir = 1;
	this->sprite.setPosition(x, y);
	this->topHitbox.setSize(Vector2f(SPRITE_DIMENSIONS.x - 2, 1.f));
	this->bottomHitbox.setSize(Vector2f(SPRITE_DIMENSIONS.x - 2, 1.f));
	this->topHitbox.setFillColor(Color::Red);
	this->bottomHitbox.setFillColor(Color::Red);
	this->topHitbox.setPosition(sprite.getPosition().x + 1, sprite.getPosition().y - 1);
	this->bottomHitbox.setPosition(sprite.getPosition().x + 1, sprite.getPosition().y + SPRITE_DIMENSIONS.y);
	this->sprite.setOrigin(SPRITE_DIMENSIONS.x / 2.f, 0.f);
	this->topHitbox.setOrigin(SPRITE_DIMENSIONS.x / 2, 0.f);
	this->bottomHitbox.setOrigin(SPRITE_DIMENSIONS.x / 2, 0.f);
	this->jumpDelay = 0;
	this->hasJumped = false;
	this->animationFrame = 0;

}

void Slime::update() {
	Tile* tileCollider = nullptr;

	for (size_t i = 0; i < slimeVector.size(); i++) {
		slimeVector[i].position = slimeVector[i].sprite.getPosition();

		if (slimeVector[i].velocity.y < TERMINAL_VELOCITY.y) {
			slimeVector[i].velocity.y += GRAVITY;
		}
		else {
			slimeVector[i].velocity.y = TERMINAL_VELOCITY.y;
		}
		slimeVector[i].position.y += slimeVector[i].velocity.y;

		slimeVector[i].topHitbox.setPosition(slimeVector[i].position.x + 1, slimeVector[i].position.y - 1);
		slimeVector[i].bottomHitbox.setPosition(slimeVector[i].position.x + 1, slimeVector[i].position.y + SPRITE_DIMENSIONS.y);

		tileCollider = slimeVector[i].isBottomColliding(true, "");
		if (tileCollider != nullptr) {
			slimeVector[i].velocity.y = 0.f;
			slimeVector[i].position.y = tileCollider->sprite.getPosition().y - SPRITE_DIMENSIONS.y;
		}
		tileCollider = slimeVector[i].isTopColliding(true, "");
		if (tileCollider != nullptr) {
			slimeVector[i].velocity.y = 0.01f;
			slimeVector[i].position.y = tileCollider->sprite.getPosition().y + tileCollider->spriteDimensions.y + 1;
		}

		tileCollider = slimeVector[i].isBottomColliding(true, "");
		if (tileCollider != nullptr) {
			slimeVector[i].sprite.setTextureRect(IntRect(0, 0, 16, 11));
			slimeVector[i].jumpDelay--;
			if (slimeVector[i].jumpDelay <= 0) {
				slimeVector[i].animationType = "jump";
				if (slimeVector[i].hasJumped == true) {
					slimeVector[i].velocity.y = -1.7f;
					slimeVector[i].position.y -= 1.f;
					slimeVector[i].jumpDelay = rand() % 360 + 120;
					slimeVector[i].animationType = "idle";
					slimeVector[i].hasJumped = false;
				}
			}
		}

		if (slimeVector[i].velocity.y != 0.f) {
			slimeVector[i].sprite.setScale(slimeVector[i].dir, 1.f);
			slimeVector[i].velocity.x = 0.4f * slimeVector[i].dir;
		}

		if (slimeVector[i].velocity.y != 0.f && slimeVector[i].isSideColliding(true, "") == nullptr) {
			slimeVector[i].position.x += slimeVector[i].velocity.x;
		}

		tileCollider = slimeVector[i].isSideColliding(true, "");
		if (tileCollider != nullptr) {
			if (slimeVector[i].dir == 1.f) {
				slimeVector[i].position.x = tileCollider->sprite.getPosition().x - ((SPRITE_DIMENSIONS.x / 2) + (tileCollider->spriteDimensions.x / 2));
			}
			else if (slimeVector[i].dir == -1.f) {
				slimeVector[i].position.x = tileCollider->sprite.getPosition().x + ((SPRITE_DIMENSIONS.x / 2) + (tileCollider->spriteDimensions.x / 2));
			}
		}

		if (slimeVector[i].sprite.getPosition().x <= Player::sprite.getPosition().x && slimeVector[i].velocity.y == 0.f) {
			slimeVector[i].dir = 1.f;
		}
		else if (slimeVector[i].sprite.getPosition().x >= Player::sprite.getPosition().x && slimeVector[i].velocity.y == 0.f) {
			slimeVector[i].dir = -1.f;
		}

		slimeVector[i].sprite.setPosition(slimeVector[i].position);
		slimeVector[i].topHitbox.setPosition(slimeVector[i].position.x + 1, slimeVector[i].position.y - 1);
		slimeVector[i].bottomHitbox.setPosition(slimeVector[i].position.x + 1, slimeVector[i].position.y + SPRITE_DIMENSIONS.y);

		if (slimeVector[i].sprite.getGlobalBounds().intersects(Player::sprite.getGlobalBounds()) && Player::showIFrames == false) {
			Player::health--;
			Player::showIFrames = true;
		}

		if (Sword::showSword == true && Sword::sprite.getGlobalBounds().intersects(slimeVector[i].sprite.getGlobalBounds())) {
			slimeVector.erase(slimeVector.begin() + i);
			Player::xp++;
		}
		else if (Player::bottomHitbox.getGlobalBounds().intersects(slimeVector[i].topHitbox.getGlobalBounds()) && Player::velocity.y > 0) {
			slimeVector.erase(slimeVector.begin() + i);
			Player::animationType = "jump";
			Player::velocity.y = -1.f;
			Player::xp++;
		}
	}
}

void Slime::draw() {
	for (size_t i = 0; i < slimeVector.size(); i++) {
		if (Game::cullingPoint.getGlobalBounds().intersects(slimeVector[i].sprite.getGlobalBounds())) {
			if (slimeVector[i].animationType == "jump") {
				slimeVector[i].jumpAnimation();
			}
			Game::window.draw(slimeVector[i].sprite);
		}
	}
}

void Slime::jumpAnimation() {
	if (animationFrame == 0) {
		sprite.setTextureRect(IntRect(0, 0, 16, 11));
	}

	else if (animationFrame == 1) {
		sprite.setTextureRect(IntRect(16, 0, 16, 11));
	}
	else if (animationFrame == 2) {
		sprite.setTextureRect(IntRect(32, 0, 16, 11));
	}
	else if (animationFrame == 3) {
		sprite.setTextureRect(IntRect(16, 0, 16, 11));
	}
	else if (animationFrame == 4) {
		sprite.setTextureRect(IntRect(0, 0, 16, 11));
	}

	if (animationClock.getElapsedTime().asSeconds() > 0.2) {
		animationFrame++;
		if (animationFrame > 4) {
			animationFrame = 0;
			hasJumped = true;
		}
		animationClock.restart();
	}
}