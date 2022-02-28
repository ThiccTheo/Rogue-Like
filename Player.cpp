#include "Player.h"

Player::Player(RenderWindow* window, string src, View* view, vector<Tile>* tileVector)
	:GRAVITY(0.025),
	TERMINAL_VELOCITY(0.f, 1.5f),
	SPRITE_SIZE(16.f),
	HITBOX_THICKNESS(1.f),
	TILE_SIZE(24.f)
{
	texture.loadFromFile(src);
	sprite.setTexture(texture);
	//temporary debugging position
	sprite.setPosition(0.f, -50.f);
	topHitbox.setSize(Vector2f(SPRITE_SIZE - 2, HITBOX_THICKNESS));
	bottomHitbox.setSize(Vector2f(SPRITE_SIZE - 2, HITBOX_THICKNESS));
	topHitbox.setFillColor(Color::Red);
	bottomHitbox.setFillColor(Color::Red);
	topHitbox.setPosition(sprite.getPosition().x + 1 , sprite.getPosition().y - 1);
	bottomHitbox.setPosition(sprite.getPosition().x + 1, sprite.getPosition().y + SPRITE_SIZE);
	sprite.setOrigin(SPRITE_SIZE / 2, 0.f);
	topHitbox.setOrigin(SPRITE_SIZE / 2, 0.f);
	bottomHitbox.setOrigin(SPRITE_SIZE / 2, 0.f);
	jumpCounter = 0;

	this->window = window;
	this->view = view;
	this->tileVector = tileVector;
}

void Player::draw() {
	//window->draw(topHitbox);
	//window->draw(bottomHitbox);
	window->draw(sprite);
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
	view->setCenter(sprite.getPosition().x + SPRITE_SIZE / 2, sprite.getPosition().y + SPRITE_SIZE / 2);

}

Tile* Player::isSideColliding() {
	Tile* collider = nullptr;
	for (int i = 0; i < tileVector->size(); i++) {
		if (sprite.getGlobalBounds().intersects(tileVector->at(i).sprite.getGlobalBounds())) {
			collider = &tileVector->at(i);
			return collider;
		}
	}
	return collider;
}

Tile* Player::isTopColliding() {
	Tile* collider = nullptr;
	for (int i = 0; i < tileVector->size(); i++) {
		if (topHitbox.getGlobalBounds().intersects(tileVector->at(i).sprite.getGlobalBounds())) {
			collider = &tileVector->at(i);
			return collider;
		}
	}
	return collider;
}

Tile* Player::isBottomColliding() {
	Tile* collider = nullptr;
	for (int i = 0; i < tileVector->size(); i++) {
		if (bottomHitbox.getGlobalBounds().intersects(tileVector->at(i).sprite.getGlobalBounds())) {
			collider = &tileVector->at(i);
			return collider;
		}
	}
	return collider;
}
