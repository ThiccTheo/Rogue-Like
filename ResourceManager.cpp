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
}