#include "ResourceManager.h"

Texture ResourceManager::tileTexture;
Texture ResourceManager::playerTexture;
Texture ResourceManager::skeletonTexture;

Image ResourceManager::START1;
Image ResourceManager::LR1;
Image ResourceManager::LRD1;
Image ResourceManager::LRU1;
Image ResourceManager::ALL1;
Image ResourceManager::EXIT1;

const int ResourceManager::START_size = 1;
const int ResourceManager::LR_size = 1;
const int ResourceManager::LRD_size = 1;
const int ResourceManager::LRU_size = 1;
const int ResourceManager::ALL_size = 1;
const int ResourceManager::EXIT_size = 1;

Image ResourceManager::START_array[ResourceManager::START_size] = { START1 };
Image ResourceManager::LR_array[ResourceManager::LR_size] = { LR1 };
Image ResourceManager::LRD_array[ResourceManager::LRD_size] = { LRD1 };
Image ResourceManager::LRU_array[ResourceManager::LRU_size] = { LRU1 };
Image ResourceManager::ALL_array[ResourceManager::ALL_size] = { ALL1 };
Image ResourceManager::EXIT_array[ResourceManager::EXIT_size] = { EXIT1 };

void ResourceManager::loadMedia() {
	tileTexture.loadFromFile("Tile/SpriteSheet.png");
	playerTexture.loadFromFile("Player/SpriteSheet.png");
	skeletonTexture.loadFromFile("Skeleton/SpriteSheet.png");

	START1.loadFromFile("Image/START/START_Test.png");
	LR1.loadFromFile("Image/LR/LR1.png");
	LRD1.loadFromFile("Image/LRD/LRD_Test.png");
	LRU1.loadFromFile("Image/LRU/LRU_Test.png");
	ALL1.loadFromFile("Image/ALL/ALL_Test.png");
	EXIT1.loadFromFile("Image/LR/LR1.png");

	/*START_array[START_size] = { START1 };
	LR_array[LR_size] = {LR1};
	LRD_array[LRD_size] = {LRD1};
	LRU_array[LRU_size] = {LRU1};
	ALL_array[ALL_size] = {ALL1};
	EXIT_array[EXIT_size] = {EXIT1};*/
}