#include "Chest.h"

vector<Chest> Chest::chestVector;

Chest::Chest(float& x, float& y){
	this->sprite.setTexture(ResourceManager::chestTexture);
	this->sprite.setTextureRect(IntRect(0, 0, 16, 16));
	this->sprite.setOrigin(8.f, 0.f);
	this->sprite.setPosition(x, y);
	this->isOpen = false;
}

void Chest::draw(){
	for (size_t i = 0; i < chestVector.size(); i++) {
		//upon collision with player, change its texture to open and set to isOpen
		if (chestVector[i].sprite.getGlobalBounds().intersects(Player::sprite.getGlobalBounds()) && chestVector[i].isOpen == false) {
			chestVector[i].isOpen = true;
			chestVector[i].sprite.setTextureRect(IntRect(16, 0, 16, 16));
		}
		Game::window.draw(chestVector[i].sprite);
	}
}
