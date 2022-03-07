#include "Player.h"

const float Player::GRAVITY = 0.025;
const float Player::SPRITE_SIZE = 16.f, Player::HITBOX_THICKNESS = 1.f;
const Vector2f Player::TERMINAL_VELOCITY = Vector2f(0.f, 1.5f);
Sprite Player::sprite;
RectangleShape Player::topHitbox, Player::bottomHitbox;
Vector2f Player::velocity, Player::position;
int Player::jumpCounter;
string Player::animationType;
Clock Player::animationClock;
int Player::walkFrame = 0;

void Player::init() {
	sprite.setTexture(ResourceManager::playerTexture);
	//temporary debugging position
	sprite.setPosition(0.f, -50.f);
	topHitbox.setSize(Vector2f(SPRITE_SIZE - 2, HITBOX_THICKNESS));
	bottomHitbox.setSize(Vector2f(SPRITE_SIZE - 2, HITBOX_THICKNESS));
	topHitbox.setFillColor(Color::Red);
	bottomHitbox.setFillColor(Color::Red);
	topHitbox.setPosition(sprite.getPosition().x + 1, sprite.getPosition().y - 1);
	bottomHitbox.setPosition(sprite.getPosition().x + 1, sprite.getPosition().y + SPRITE_SIZE);
	sprite.setOrigin(SPRITE_SIZE / 2, 0.f);
	topHitbox.setOrigin(SPRITE_SIZE / 2, 0.f);
	bottomHitbox.setOrigin(SPRITE_SIZE / 2, 0.f);
	jumpCounter = 0;
	animationType = "idle";
}

void Player::draw() 
{
	if (animationType == "idle") {
		sprite.setTextureRect(IntRect(0, 0, 16, 16));
	}
	else if (animationType == "walk") {
		walkAnimation();
	}
	else if (animationType == "jump") {
		sprite.setTextureRect(IntRect(48, 0, 16, 16));
	}

	Game::window.draw(sprite);
}

void Player::update() {
	Tile* tileCollider = nullptr;

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
	
	tileCollider = isBottomColliding();
	if (tileCollider != nullptr && tileCollider->isPassable == false) {
		velocity.y = 0.f;
		position.y = tileCollider->sprite.getPosition().y - SPRITE_SIZE;
	}

	tileCollider = isTopColliding();
	if (tileCollider != nullptr && tileCollider->isPassable == false) {
		velocity.y = 0.1f;
		position.y = tileCollider->sprite.getPosition().y + Tile::SPRITE_SIZE + 1;
	}

	tileCollider = isBottomColliding();
	if (Keyboard::isKeyPressed(Keyboard::W) && jumpCounter == 0) {
		jumpCounter++;
		if (Keyboard::isKeyPressed(Keyboard::W) && tileCollider != nullptr && tileCollider->isPassable == false) {
			position.y -= 1.f;
			velocity.y = -1.7f;
			animationType = "jump";
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		if (velocity.y == 0) {
			animationType = "walk";
		}
		sprite.setScale(-1.f, 1.f);
		position.x -= 1.f;
		sprite.setPosition(position);
		tileCollider = isSideColliding();
		if (tileCollider != nullptr && tileCollider->isPassable == false) {
			position.x = tileCollider->sprite.getPosition().x + ((SPRITE_SIZE / 2) + (Tile::SPRITE_SIZE / 2));
		}
	}

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		if (velocity.y == 0) {
			animationType = "walk";
		}
		sprite.setScale(1.f, 1.f);
		position.x += 1.f;
		sprite.setPosition(position);
		tileCollider = isSideColliding();
		if (tileCollider != nullptr && tileCollider->isPassable == false) {
			position.x = tileCollider->sprite.getPosition().x - ((SPRITE_SIZE / 2) + (Tile::SPRITE_SIZE / 2));
		}
	}

	if (velocity.y == 0.f && animationType == "jump" && Keyboard::isKeyPressed(Keyboard::W)) {
		animationType = "idle";
	}

	if (velocity.y != 0.f && animationType != "jump") {
		animationType = "idle";
	}

	if (velocity.y == 0.f) {
		if (!Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::W)) {
			animationType = "idle";
		}
	}

	sprite.setPosition(position);
	topHitbox.setPosition(position.x + 1, position.y - 1);
	bottomHitbox.setPosition(position.x + 1, position.y + 16.f);
	Game::view.setCenter(sprite.getPosition().x + SPRITE_SIZE / 2, sprite.getPosition().y + SPRITE_SIZE / 2);
	Game::cullingPoint.setPosition(Game::view.getCenter());

	tileCollider = isSideColliding();
	if (tileCollider != nullptr && tileCollider->type == "exit" && Keyboard::isKeyPressed(Keyboard::Space)) {
		Game::loadLevel();
	}
}

Tile* Player::isSideColliding() {
	Tile* collider = nullptr;
	for (int i = 0; i < Tile::tileVector.size(); i++) {
		if (sprite.getGlobalBounds().intersects(Tile::tileVector[i].sprite.getGlobalBounds())) {
			collider = &Tile::tileVector[i];
			return collider;
		}
	}
	return collider;
}

Tile* Player::isTopColliding() {
	Tile* collider = nullptr;
	for (int i = 0; i < Tile::tileVector.size(); i++) {
		if (topHitbox.getGlobalBounds().intersects(Tile::tileVector[i].sprite.getGlobalBounds())) {
			collider = &Tile::tileVector[i];
			return collider;
		}
	}
	return collider;
}

Tile* Player::isBottomColliding() {
	Tile* collider = nullptr;
	for (int i = 0; i < Tile::tileVector.size(); i++) {
		if (bottomHitbox.getGlobalBounds().intersects(Tile::tileVector[i].sprite.getGlobalBounds())) {
			collider = &Tile::tileVector[i];
			return collider;
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
