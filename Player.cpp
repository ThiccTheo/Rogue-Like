#include "Player.h"

const float Player::GRAVITY = 0.025;
const float Player::SPRITE_SIZE = 16.f, Player::HITBOX_THICKNESS = 1.f, Player::TILE_SIZE = 24.f;
const Vector2f Player::TERMINAL_VELOCITY = Vector2f(0.f, 1.5f);
Sprite Player::sprite;
RectangleShape Player::topHitbox, Player::bottomHitbox;
Vector2f Player::velocity, Player::position;
int Player::jumpCounter;

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
}

void Player::draw() 
{
	Game::window.draw(topHitbox);
	Game::window.draw(bottomHitbox);
	Game::window.draw(sprite);
}

void Player::update() {

	position = sprite.getPosition();
	if (isBottomColliding() != nullptr) {
		velocity.y = 0.f;
		position.y = isBottomColliding()->sprite.getPosition().y - SPRITE_SIZE;
	}
	else if (isTopColliding() != nullptr) {
		velocity.y = 0.f;
		position.y = isTopColliding()->sprite.getPosition().y + TILE_SIZE + 1;
	}
	else {
		if (velocity.y < TERMINAL_VELOCITY.y) {
			velocity.y += GRAVITY;
		}
		else{
			velocity.y = TERMINAL_VELOCITY.y;
		}
		position.y += velocity.y;
	}

	if (Keyboard::isKeyPressed(Keyboard::W) && jumpCounter == 0) {
		jumpCounter++;
		if (Keyboard::isKeyPressed(Keyboard::W) && isTopColliding() == nullptr && isBottomColliding() != nullptr) {
			position.y -= 1.f;
			velocity.y = -1.75f;
		}
	}

	//acceleration
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		sprite.setScale(-1.f, 1.f);
		//velocity.x -= 3.f;
		position.x -= 1.f;
		sprite.setPosition(position);
		if (isSideColliding() != nullptr) {
			position.x += 1.f;
		}

	}
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		sprite.setScale(1.f, 1.f);
		//velocity.x += 3.f;
		position.x += 1.f;
		sprite.setPosition(position);
		if (isSideColliding() != nullptr) {
			position.x -= 1.f;
		}
	}
	//else{} (decay)

	sprite.setPosition(position);
	topHitbox.setPosition(position.x + 1, position.y - 1);
	bottomHitbox.setPosition(position.x + 1, position.y + 16.f);
	Game::view.setCenter(sprite.getPosition().x + SPRITE_SIZE / 2, sprite.getPosition().y + SPRITE_SIZE / 2);
	Game::cullingPoint.setPosition(Game::view.getCenter());

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
