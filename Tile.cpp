#include "Tile.h"

const float  Tile::POSITION_SCALAR = 24.f, Tile::SPRITE_SIZE = 24.f, Tile::SCALE = 1.5;
const int Tile::START_TILE = 1, Tile::DOWN_TILE = 2, Tile::UP_TILE = 3, Tile::UP_AND_DOWN_TILE = 4, Tile::DOOR_TILE = 5;

vector<Tile> Tile::tileVector;

Tile::Tile(float& x, float& y){
	this->sprite.setScale(SCALE, SCALE);
	this->sprite.setTexture(ResourceManager::tileTexture);
	this->sprite.setOrigin(SPRITE_SIZE / (POSITION_SCALAR / 8.f), 0.f);
	this->sprite.setPosition(x, y);
}

void Tile::initTiles(int& levelPosX, int& levelPosY, const Image& image) {
	Color color;

	float x = 0.f, y = 0.f;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 10; j++) {
			x = POSITION_SCALAR * (j + (10 * levelPosX));
			y = POSITION_SCALAR * (i + (8 * levelPosY));

			color = image.getPixel(j, i);

			if (color == Color(255, 0, 0, 255)) {
				tileVector.push_back(Tile(x, y));
			}
			else if (color == Color(0, 255, 0, 255)) {
				y += 8.f;
				Skeleton::skeletonVector.push_back(Skeleton(x, y));
			}
			else if (color == Color(0, 0, 255, 255)) {
				y += 8.f;
				Player::sprite.setPosition(x, y);
			}
		}
	}
}

void Tile::draw() {
	for (int i = 0; i < tileVector.size(); i++) {
		if (tileVector[i].sprite.getGlobalBounds().intersects(Game::cullingPoint.getGlobalBounds())) {
			Game::window.draw(tileVector[i].sprite);
		}
	}
}

void Tile::createLevelPathing() {
	Image image;
	int pos = 0;
	int roomMatrix[4][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
	};

	for (int i = 0; i < 3; i++) {
		pos = rand() % 4;
		if (i > 0 && roomMatrix[i - 1][pos] == 2) {
			roomMatrix[i][pos] = UP_AND_DOWN_TILE;
		}
		else {
			roomMatrix[i][pos] = DOWN_TILE;
		}
		roomMatrix[i + 1][pos] = UP_TILE;
	}

	do {
		pos = rand() % 4;
	} while (roomMatrix[0][pos] == 2);
	roomMatrix[0][pos] = START_TILE;

	do {
		pos = rand() % 4;
	} while (roomMatrix[3][pos] == 3);
	roomMatrix[3][pos] = DOOR_TILE;

	cout << "Level Layout:\n";
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << roomMatrix[i][j] << ", ";
			image = getRoomTemplate(roomMatrix[i][j]);
			initTiles(j, i, image);
		}
		cout << endl;
	}
}

Image Tile::getRoomTemplate(int& templateType) {
	Image image;
	int randomPick = 0;

	switch (templateType) {
	case 0: /*randomPick = rand() % ResourceManager::LR_size; image = ResourceManager::LR_array[randomPick]; break; */ image = ResourceManager::LR1; break;
	case 1: /*randomPick = rand() % ResourceManager::START_size; image = ResourceManager::START_array[randomPick]; break;*/image = ResourceManager::START1; break;
	case 2: /*randomPick = rand() % ResourceManager::LRD_size; image = ResourceManager::LRD_array[randomPick]; break;*/image = ResourceManager::LRD1; break;
	case 3: /*randomPick = rand() % ResourceManager::LRU_size; image = ResourceManager::LRU_array[randomPick]; break;*/image = ResourceManager::LRU1; break;
	case 4: /*randomPick = rand() % ResourceManager::ALL_size; image = ResourceManager::ALL_array[randomPick]; break;*/image = ResourceManager::ALL1; break;
	case 5: /*randomPick = rand() % ResourceManager::EXIT_size; image = ResourceManager::EXIT_array[randomPick]; break;*/image = ResourceManager::EXIT1; break;
	default: /*randomPick = rand() % ResourceManager::LR_size; image = ResourceManager::LR_array[randomPick];*/image = ResourceManager::LR1; break;
	}

	if (rand() % 2 == 1) image.flipHorizontally();

	return image;

}

