#include "Entity.h"
#include "Tile.h"

Tile* Entity::isSideColliding(bool isSolid, string&& type) {
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

Tile* Entity::isTopColliding(bool isSolid, string&& type) {
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

Tile* Entity::isBottomColliding(bool isSolid, string&& type) {
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