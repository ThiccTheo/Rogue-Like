#include "Slime.h"

vector<Slime> Slime::slimeVector;
const Vector2f Slime::SPRITE_DIMENSIONS = Vector2f(16.f, 11.f);

const float Slime::GRAVITY = 0.025f;
const Vector2f Slime::TERMINAL_VELOCITY = Vector2f(0.f, 1.5f);

Slime::Slime(float& x, float& y) {
	this->sprite.setTexture(ResourceManager::slimeTexture);
	this->dir = 'R';
	this->sprite.setPosition(x, y);
	this->topHitbox.setSize(Vector2f(SPRITE_DIMENSIONS.x - 2, 1.f));
	this->bottomHitbox.setSize(Vector2f(SPRITE_DIMENSIONS.x - 2, 1.f));
	this->topHitbox.setFillColor(Color::Red);
	this->bottomHitbox.setFillColor(Color::Red);
	this->topHitbox.setPosition(sprite.getPosition().x + 1, sprite.getPosition().y - 1);
	this->bottomHitbox.setPosition(sprite.getPosition().x + 1, sprite.getPosition().y + SPRITE_DIMENSIONS.y);
	this->sprite.setOrigin(SPRITE_DIMENSIONS.x / 2, 0.f);
	this->topHitbox.setOrigin(SPRITE_DIMENSIONS.x / 2, 0.f);
	this->bottomHitbox.setOrigin(SPRITE_DIMENSIONS.x / 2, 0.f);
}

void Slime::update() {
	Tile* tileCollider = nullptr;

	for (size_t i = 0; i < slimeVector.size(); i++) {
		slimeVector[i].position = slimeVector[i].sprite.getPosition();

		tileCollider = slimeVector[i].isBottomColliding(true, "");
		if (tileCollider != nullptr) {
			slimeVector[i].velocity.y = 0.f;
			slimeVector[i].position.y = tileCollider->sprite.getPosition().y - SPRITE_DIMENSIONS.y;
			tileCollider = slimeVector[i].isTopColliding(true, "");
		}
		else if (tileCollider != nullptr) {
			slimeVector[i].velocity.y = 0.1f;
			slimeVector[i].position.y = tileCollider->sprite.getPosition().y + tileCollider->spriteDimensions.y + 1;
		}
		else {
			if (slimeVector[i].velocity.y < TERMINAL_VELOCITY.y) {
				slimeVector[i].velocity.y += GRAVITY;
			}
			else {
				slimeVector[i].velocity.y = TERMINAL_VELOCITY.y;
			}
			slimeVector[i].position.y += slimeVector[i].velocity.y;
		}

		if (slimeVector[i].dir == 'R') {
			slimeVector[i].sprite.setScale(1.f, 1.f);
			slimeVector[i].velocity.x = 1.0f;
		}
		else if (slimeVector[i].dir == 'L') {
			slimeVector[i].sprite.setScale(-1.f, 1.f);
			slimeVector[i].velocity.x = -1.0f;
		}

		slimeVector[i].position.x += slimeVector[i].velocity.x;

		tileCollider = slimeVector[i].isSideColliding(true, "");
		if (tileCollider != nullptr) {
			if (slimeVector[i].dir == 'R') {
				slimeVector[i].dir = 'L';
				slimeVector[i].position.x = tileCollider->sprite.getPosition().x - ((SPRITE_DIMENSIONS.x / 2) + (tileCollider->spriteDimensions.x / 2));
			}
			else if (slimeVector[i].dir == 'L') {
				slimeVector[i].dir = 'R';
				slimeVector[i].position.x = tileCollider->sprite.getPosition().x + ((SPRITE_DIMENSIONS.x / 2) + (tileCollider->spriteDimensions.x / 2));
			}
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
	}
}

void Slime::draw() {
	for (size_t i = 0; i < slimeVector.size(); i++) {
		Game::window.draw(slimeVector[i].sprite);
	}
}


Tile* Slime::isSideColliding(bool isSolid, string&& type) {
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

Tile* Slime::isTopColliding(bool isSolid, string&& type) {
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

Tile* Slime::isBottomColliding(bool isSolid, string&& type) {
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