#include "Chest.h"

vector<Chest> Chest::chestVector;

Chest::Chest(float& x, float& y){
	this->sprite.setTexture(ResourceManager::chestTexture);
	this->sprite.setTextureRect(IntRect(0, 0, 16, 12));
	this->sprite.setOrigin(8.f, 0.f);
	this->sprite.setPosition(x, y);
	this->isOpen = false;
}

void Chest::draw(){
	for (size_t i = 0; i < chestVector.size(); i++) {
		if (chestVector[i].isOpen == false && chestVector[i].sprite.getGlobalBounds().intersects(Player::sprite.getGlobalBounds())) {
			chestVector[i].isOpen = true;
			chestVector[i].sprite.setTextureRect(IntRect(16, 0, 16, 12));
			chestVector[i].dropLoot();
		}
		if (Game::cullingPoint.getGlobalBounds().intersects(chestVector[i].sprite.getGlobalBounds())) {
			Game::window.draw(chestVector[i].sprite);
		}
	}
}

void Chest::dropLoot() {
	int rnJesus = rand() % 4;
	if (rnJesus == 0) Player::xp += 2;
	else if (rnJesus == 1) { if (Sword::damage < Sword::MAX_DAMAGE) Sword::damage++; else Player::xp += 5; }
	else if (rnJesus == 2) { if (Player::speed < Player::TERMINAL_VELOCITY.x) Player::speed += 0.1f; else Player::xp += 5; }
	else if (rnJesus == 3) { if (Sword::clickDelay > 0.f) Sword::clickDelay -= 0.1f; else Player::xp += 5; }
	
}