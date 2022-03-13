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

	tileTexture.loadFromFile("ResourceManager/TileSpriteSheet.png");
	backgroundTexture.loadFromFile("ResourceManager/Background.png");
	playerTexture.loadFromFile("ResourceManager/PlayerSpriteSheet.png");
	skeletonTexture.loadFromFile("ResourceManager/SkeletonSpriteSheet.png");
	chestTexture.loadFromFile("ResourceManager/ChestSpriteSheet.png");
	swordTexture.loadFromFile("ResourceManager/SwordSpriteSheet.png");
	slimeTexture.loadFromFile("ResourceManager/SlimeSpriteSheet.png");

	START_array[0].loadFromFile("ResourceManager/START/START1.png");
	LR_array[0].loadFromFile("ResourceManager/LR/LR1.png");
	LRD_array[0].loadFromFile("ResourceManager/LRD/LRD1.png");
	LRU_array[0].loadFromFile("ResourceManager/LRU/LRU1.png");
	ALL_array[0].loadFromFile("ResourceManager/ALL/ALL1.png");
	EXIT_array[0].loadFromFile("ResourceManager/EXIT/EXIT1.png");
}