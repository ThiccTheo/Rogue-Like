#include "Sword.h"

Clock Sword::animationClock;
Sprite Sword::sprite;

int Sword::damage = 1;
int Sword::attackFrame = 0;
int Sword::clickCounter = 0;

const int Sword::MAX_DAMAGE = 5;

bool Sword::showSword = false;

float Sword::clickDelay = 1.f;

void Sword::init() {
	sprite.setTexture(ResourceManager::swordTexture);
	sprite.setOrigin(8.f, 0.f);
}

void Sword::update() {
	sprite.setScale(Player::sprite.getScale());
	sprite.setPosition((Player::sprite.getPosition().x + (Player::sprite.getScale()).x * 11), Player::sprite.getPosition().y - 3);
	if (Mouse::isButtonPressed(Mouse::Left) && clickCounter == 0) {
		clickCounter++;
		if (Mouse::isButtonPressed(Mouse::Left)) {
			showSword = true;
		}
	}
}
	

void Sword::draw() {
	if (showSword == true) {
		attackAnimation();

		if (Player::showIFrames == false) {
			Game::window.draw(sprite);
		}
		else if (Player::showIFrames == true) {
			if (Player::iFrameCounter >= Player::iFrameNumber) {
				Game::window.draw(sprite);
				Player::iFrameCounter = 0;
				Player::iFrameCycles++;
			}
			if (Player::iFrameCycles >= Player::iFrameCycleNumber) {
				Player::iFrameCycles = 0;
				Player::iFrameCounter = 0;
				Player::showIFrames = false;
			}

		}
	}
}

void Sword::attackAnimation() {
	if (attackFrame == 0 || attackFrame == 1) {
		sprite.setTextureRect(IntRect(0, 0, 16, 16));
	}

	else if (attackFrame == 2) {
		sprite.setTextureRect(IntRect(16, 0, 16, 16));
	}

	else if (attackFrame == 3) {
		sprite.setTextureRect(IntRect(32, 0, 15, 16));
	}

	if (animationClock.getElapsedTime().asSeconds() >= 0.1) {
		attackFrame++;
		if (attackFrame > 3) {
			attackFrame = 0;
			showSword = false;
		}
		animationClock.restart();
	}
}