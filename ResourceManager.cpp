#include "ResourceManager.h"

Texture ResourceManager::tileTexture;
Texture ResourceManager::playerTexture;
Texture ResourceManager::skeletonTexture;

void ResourceManager::loadMedia() {
	tileTexture.loadFromFile("Tile/Sprite.png");
	playerTexture.loadFromFile("Player/sprite.png");
	skeletonTexture.loadFromFile("Skeleton/s.png");
}