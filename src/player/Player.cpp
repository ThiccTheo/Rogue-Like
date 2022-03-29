#include "Player.h"
#include "../tile/Tile.h"
#include "../resource/ResourceManager.h"
#include "../game/Game.h"
#include "../weapon/sword/Sword.h"

Sprite Player::sprite;
RectangleShape Player::topHitbox, Player::bottomHitbox;
Vector2f Player::velocity, Player::position;

string Player::animationType = "idle";
Clock Player::animationClock;

const int Player::iFrameCycleNumber = 15;
const int Player::iFrameNumber = 5;

const float Player::GRAVITY = 0.025f;
const float Player::SPRITE_SIZE = 16.f, Player::HITBOX_THICKNESS = 1.f;
const Vector2f Player::TERMINAL_VELOCITY = Vector2f(1.5f, 1.5f);

const int Player::XP_LIMIT = 10;

int Player::jumpCounter = 0;
int Player::walkFrame = 0;
int Player::health = 3;
int Player::iFrameCycles = 0;
int Player::iFrameCounter = 0;
bool Player::showIFrames;
int Player::meleeFrame = 0;

float Player::speed = 1;
int Player::xp = 0;

void Player::init() {
	sprite.setTexture(ResourceManager::playerTexture);
	topHitbox.setSize(Vector2f(SPRITE_SIZE - 2, HITBOX_THICKNESS));
	bottomHitbox.setSize(Vector2f(SPRITE_SIZE - 2, HITBOX_THICKNESS));
	topHitbox.setFillColor(Color::Red);
	bottomHitbox.setFillColor(Color::Red);
	topHitbox.setPosition(sprite.getPosition().x + 1, sprite.getPosition().y - 1);
	bottomHitbox.setPosition(sprite.getPosition().x + 1, sprite.getPosition().y + SPRITE_SIZE);
	sprite.setOrigin(SPRITE_SIZE / 2, 0.f);
	topHitbox.setOrigin(SPRITE_SIZE / 2, 0.f);
	bottomHitbox.setOrigin(SPRITE_SIZE / 2, 0.f);
}

void Player::draw() 
{

	if (animationType == "idle") {
		sprite.setTextureRect(IntRect(0, 0, 16, 16));
		Sword::attackFrame = 0;
	}
	else if (animationType == "melee") {
		meleeAnimation();
	}
	else if (animationType == "walk") {
		walkAnimation();
	}
	if (animationType == "jump" && Sword::showSword == true) {
		sprite.setTextureRect(IntRect(0, 0, 16, 16));
	}
	else if (animationType == "jump") {
		sprite.setTextureRect(IntRect(48, 0, 16, 16));
	}

	if (showIFrames == false) {
		Game::window.draw(sprite);
	}
	else if (showIFrames == true) {
		if (iFrameCounter >= iFrameNumber) {
			Game::window.draw(sprite);
			iFrameCounter = 0;
			iFrameCycles++;
		}
		if (iFrameCycles >= iFrameCycleNumber) {
			iFrameCycles = 0;
			iFrameCounter = 0;
			showIFrames = false;
		}

	}
}

void Player::update() {
	Tile* tileCollider = nullptr;
	iFrameCounter++;

	position = sprite.getPosition();

	if (velocity.y < TERMINAL_VELOCITY.y) {
		velocity.y += GRAVITY;
	}
	else {
		velocity.y = TERMINAL_VELOCITY.y;
	}
	position.y += velocity.y;
	
	topHitbox.setPosition(position.x + 1, position.y - 1);
	bottomHitbox.setPosition(position.x + 1, position.y + SPRITE_SIZE);
	
	tileCollider = isBottomColliding(true, "");
	if (tileCollider != nullptr) {
		velocity.y = 0.f;
		position.y = tileCollider->sprite.getPosition().y - SPRITE_SIZE;
	}

	tileCollider = isTopColliding(true, "");
	if (tileCollider != nullptr) {
		velocity.y = 0.1f;
		position.y = tileCollider->sprite.getPosition().y + tileCollider->spriteDimensions.y + 1;
	}

	tileCollider = isBottomColliding(true, "");
	if (Keyboard::isKeyPressed(Keyboard::W) && jumpCounter == 0) {
		jumpCounter++;
		if (Keyboard::isKeyPressed(Keyboard::W) && tileCollider != nullptr) {
			position.y -= 1.f;
			velocity.y = -1.7f;
			animationType = "jump";
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		if (velocity.y == 0 && animationType != "melee") {
			animationType = "walk";
		}
		sprite.setScale(1.f, 1.f);
		position.x += speed;
		sprite.setPosition(position);
		tileCollider = isSideColliding(true, "");
		if (tileCollider != nullptr) {
			position.x = tileCollider->sprite.getPosition().x - ((SPRITE_SIZE / 2) + (tileCollider->spriteDimensions.x / 2));
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		if (velocity.y == 0 && animationType != "melee") {
			animationType = "walk";
		}
		sprite.setScale(-1.f, 1.f);
		position.x -= speed;
		sprite.setPosition(position);
		tileCollider = isSideColliding(true, "");
		if (tileCollider != nullptr) {
			position.x = tileCollider->sprite.getPosition().x + ((SPRITE_SIZE / 2) + (tileCollider->spriteDimensions.x / 2));
		}
	}

	if (animationType != "melee") {
		if (velocity.y != 0.f && animationType != "jump") {
			animationType = "idle";
		}

		if (velocity.y == 0.f) {
			if (animationType == "jump" && Keyboard::isKeyPressed(Keyboard::W)) {
				animationType = "idle";
			}
			if (!Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::W)) {
				animationType = "idle";
			}
			if (Keyboard::isKeyPressed(Keyboard::W) && animationType == "walk" && !Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D)) {
				animationType = "idle";
			}
		}
	}

	sprite.setPosition(position);
	topHitbox.setPosition(position.x + 1, position.y - 1);
	bottomHitbox.setPosition(position.x + 1, position.y + 16.f);
	Game::view.setCenter(sprite.getPosition().x + SPRITE_SIZE / 2, sprite.getPosition().y + SPRITE_SIZE / 2);
	Game::cullingPoint.setPosition(Game::view.getCenter());

	tileCollider = isSideColliding(false, "exit");
	if (tileCollider != nullptr && Keyboard::isKeyPressed(Keyboard::Space)) {
		Game::loadLevel();
	}

	if (health <= 0) {
		health = 0;
	}
	if (xp >= XP_LIMIT) {
		health++;
		xp -= XP_LIMIT;
	}
}

Tile* Player::isSideColliding(bool isSolid, string&& type) {
	Tile* collider = nullptr;
	for (size_t i = 0; i < Tile::tileVector.size(); i++) {
		if (sprite.getGlobalBounds().intersects(Tile::tileVector[i].sprite.getGlobalBounds()) && Tile::tileVector[i].isSolid == isSolid) {
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

Tile* Player::isTopColliding(bool isSolid, string&& type) {
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

Tile* Player::isBottomColliding(bool isSolid, string&& type) {
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

void Player::walkAnimation() {
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

void Player::meleeAnimation() {
	if (meleeFrame == 0 || meleeFrame == 1) {
		sprite.setTextureRect(IntRect(0, 16, 16, 16));
	}

	else if (meleeFrame == 2 || meleeFrame == 3) {
		sprite.setTextureRect(IntRect(16, 16, 16, 16));
	}

	if (animationClock.getElapsedTime().asSeconds() > 0.1) {
		meleeFrame++;
		if (meleeFrame > 3) {
			meleeFrame = 0;
			animationType = "idle";
		}
		animationClock.restart();
	}
}