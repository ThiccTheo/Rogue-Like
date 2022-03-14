#include "Tile.h"

const float  Tile::POSITION_SCALAR = 24.f, Tile::SCALE = 1.5;
const int Tile::START_TILE = 1, Tile::DOWN_TILE = 2, Tile::UP_TILE = 3, Tile::UP_AND_DOWN_TILE = 4, Tile::DOOR_TILE = 5;

vector<Tile> Tile::tileVector;

Tile::Tile(float& x, float& y, string&& type, bool isSolid){
	this->spriteDimensions = Vector2f(24.f, 24.f);
	this->sprite.setScale(SCALE, SCALE);
	this->sprite.setTexture(ResourceManager::tileTexture);
	this->sprite.setOrigin(8.f, 0.f);
	this->sprite.setPosition(x, y);
	this->isSolid = isSolid;
	this->type = type;

	if (type == "stone") {
		this->sprite.setTextureRect(IntRect(0, 0, 16, 16));
	}
	else if (type == "start") {
		this->sprite.setTextureRect(IntRect(16, 0, 16, 16));
	}
	else if (type == "exit") {
		this->sprite.setTextureRect(IntRect(32, 0, 16, 16));
	}
}

void Tile::initTiles(int& levelPosX, int& levelPosY, const Image& image) {
	Color color;
	float x = 0.f, y = 0.f;

	/*
	THESE VALUES ARE SUBJECT TO CHANGE

	stone: #ff0000 | 255, 0, 0
	skeleton: #00ff00 | 0, 255, 0
	start: #0000ff | 0, 0, 255
	exit: #ffff00 | 255, 255, 0
	chest: #ff00ff | 255, 0, 255
	slime: #800080 | 128, 0, 128
	*/


	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 10; j++) {
			x = POSITION_SCALAR * (j + (10 * levelPosX));
			y = POSITION_SCALAR * (i + (8 * levelPosY));

			color = image.getPixel(j, i);

			if (color == Color(255, 0, 0)) {
				tileVector.push_back(Tile(x, y, "stone", true));
			}
			else if (color == Color(0, 255, 0)) {
				y += 8.f;
				if (rand() % 5 >= 0) Skeleton::skeletonVector.push_back(Skeleton(x, y));
			}
			else if (color == Color(0, 0, 255)) {
				y += 8.f;
				Player::sprite.setPosition(x, y);
				y -= 8.f;
				tileVector.push_back(Tile(x, y, "start", false));
			}
			else if (color == Color(255, 255, 0)) {
				tileVector.push_back(Tile(x, y, "exit", false));
			}
			else if (color == Color(255, 0, 255)) {
				y += 12.f;
				if (rand() % 5 >= 0) Chest::chestVector.push_back(Chest(x, y));
			}
			else if (color == Color(128, 0, 128)) {
				y += 8.f;
				if (rand() % 5 >= 0) Slime::slimeVector.push_back(Slime(x, y));
			}
		}
	}
}

void Tile::draw() {
	for (size_t i = 0; i < tileVector.size(); i++) {
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
		if (i > 0 && (roomMatrix[i - 1][pos] == DOWN_TILE || roomMatrix[i - 1][pos] == UP_AND_DOWN_TILE)) {
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
		cout << '\n';
	}
}

Image Tile::getRoomTemplate(int& templateType) {
	Image image;

	switch (templateType) {
		case 0: image = ResourceManager::LR_array[rand() % ResourceManager::LR_size]; break;
		case 1: image = ResourceManager::START_array[rand() % ResourceManager::START_size]; break;
		case 2: image = ResourceManager::LRD_array[rand() % ResourceManager::LRD_size]; break;
		case 3: image = ResourceManager::LRU_array[rand() % ResourceManager::LRU_size]; break;
		case 4: image = ResourceManager::ALL_array[rand() % ResourceManager::ALL_size]; break;
		case 5: image = ResourceManager::EXIT_array[rand() % ResourceManager::EXIT_size]; break;
		default: image = ResourceManager::LR_array[rand() % ResourceManager::LR_size];
	}

	if (rand() % 2 == 1) image.flipHorizontally();

	return image;

}

void Tile::setupBackground() {
	int backgroundArray[6][6] = {
		{1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1},
	};

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (backgroundArray[i][j] == 0) {
				tileVector.push_back(Tile(j, i, false));
			}
			if (backgroundArray[i][j] == 1) {
				tileVector.push_back(Tile(j, i, true));
			}
		}
	}
}

Tile::Tile(int& x, int& y, bool isSolid) {
	this->spriteDimensions = Vector2f(240.f, 192.f);
	//240 x 192 pixels per room
	//image needs to be 80 x 64 pixels
	this->isSolid = isSolid;
	this->sprite.setTexture(ResourceManager::backgroundTexture);
	if (this->isSolid == true) {
		this->sprite.setTextureRect(IntRect(0, 0, 80, 64));
	}
	else if (this->isSolid == false) {
		this->sprite.setTextureRect(IntRect(80, 0, 80, 64));
	}
	this->sprite.setScale(3.f, 3.f);
	this->sprite.setOrigin(40.f, 0.f);
	this->sprite.setPosition(static_cast<float>(- 132 + (x * 240)), static_cast<float>(- 192 + (y * 192)));
}