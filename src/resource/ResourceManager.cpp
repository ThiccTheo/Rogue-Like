#include "ResourceManager.h"

Texture ResourceManager::tileTexture;
Texture ResourceManager::backgroundTexture;
Texture ResourceManager::playerTexture;
Texture ResourceManager::skeletonTexture;
Texture ResourceManager::chestTexture;
Texture ResourceManager::swordTexture;
Texture ResourceManager::slimeTexture;

const int ResourceManager::START_size = 1;
const int ResourceManager::LR_size = 1;
const int ResourceManager::LRD_size = 1;
const int ResourceManager::LRU_size = 1;
const int ResourceManager::ALL_size = 1;
const int ResourceManager::EXIT_size = 1;

Image ResourceManager::START_array[ResourceManager::START_size] = {Image()};
Image ResourceManager::LR_array[ResourceManager::LR_size] = {Image()};
Image ResourceManager::LRD_array[ResourceManager::LRD_size] = {Image()};
Image ResourceManager::LRU_array[ResourceManager::LRU_size] = {Image()};
Image ResourceManager::ALL_array[ResourceManager::ALL_size] = {Image()};
Image ResourceManager::EXIT_array[ResourceManager::EXIT_size] = {Image()};

void ResourceManager::loadMedia() {

	tileTexture.loadFromFile("src/tile/spritesheet.png");
	backgroundTexture.loadFromFile("src/resource/Background.png");
	playerTexture.loadFromFile("src/player/spritesheet.png");
	skeletonTexture.loadFromFile("src/entity/skeleton/spritesheet.png");
	chestTexture.loadFromFile("src/chest/spritesheet.png");
	swordTexture.loadFromFile("src/weapon/sword/spritesheet.png");
	slimeTexture.loadFromFile("src/entity/slime/spritesheet.png");

	START_array[0].loadFromFile("src/resource/START/START1.png");
	LR_array[0].loadFromFile("src/resource/LR/LR1.png");
	LRD_array[0].loadFromFile("src/resource/LRD/LRD1.png");
	LRU_array[0].loadFromFile("src/resource/LRU/LRU1.png");
	ALL_array[0].loadFromFile("src/resource/ALL/ALL1.png");
	EXIT_array[0].loadFromFile("src/resource/EXIT/EXIT1.png");
}