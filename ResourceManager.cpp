#include "ResourceManager.h"

Texture ResourceManager::tileTexture;
Texture ResourceManager::playerTexture;
Texture ResourceManager::skeletonTexture;

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
	tileTexture.loadFromFile("Tile/SpriteSheet.png");
	playerTexture.loadFromFile("Player/SpriteSheet.png");
	skeletonTexture.loadFromFile("Skeleton/SpriteSheet.png");

	START_array[0].loadFromFile("Image/START/START_Test.png");
	LR_array[0].loadFromFile("Image/LR/LR1.png");
	LRD_array[0].loadFromFile("Image/LRD/LRD_Test.png");
	LRU_array[0].loadFromFile("Image/LRU/LRU_Test.png");
	ALL_array[0].loadFromFile("Image/ALL/ALL_Test.png");
	EXIT_array[0].loadFromFile("Image/LR/LR1.png");
}