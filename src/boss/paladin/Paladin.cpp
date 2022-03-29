#include "Paladin.h"
#include "../../resource/ResourceManager.h"
#include "../../game/Game.h"
#include "../../tile/Tile.h"
#include "../../player/Player.h"

Sprite Paladin::sprite;
bool Paladin::flag = false;
float Paladin::dir = -1;
Vector2f Paladin::velocity = Vector2f(1.f, 0.f);
Vector2f Paladin::position = Vector2f(0.f, 0.f);

void Paladin::init() {
	sprite.setTexture(ResourceManager::paladinTexture);
	sprite.setOrigin(8.f, 0.f);
    sprite.setPosition(0.f, 720.f);
	position = sprite.getPosition();
	flag = true;
}

void Paladin::draw() {
	if (flag == true) {
		Game::window.draw(sprite);
	}
}

void Paladin::update() {
	if (flag == true) {
		Tile* tileCollider = isSideColliding(true, "");
		if (tileCollider != nullptr) {
			dir *= -1.f;
		}

		sprite.setScale(dir, 1.f);

		velocity.x = dir;

		position.x += velocity.x;
		sprite.setPosition(position);

		if (sprite.getGlobalBounds().intersects(Player::sprite.getGlobalBounds()) && Player::showIFrames == false) {
			Player::health--;
			Player::showIFrames = true;
		}
		
	}
}

Tile* Paladin::isSideColliding(bool isSolid, string&& type) {
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