#include "Tile.h"

Tile::Tile(RenderWindow* window, vector<Tile>* tileVector, vector<Skeleton>* skeletonVector)
	:SPRITE_SIZE(24.f), POSITION_SCALAR(24.f), SCALE(1.5),
	START_TILE(1), DOWN_TILE(2), UP_TILE(3), UP_AND_DOWN_TILE(4), DOOR_TILE(5)
{
	this->tileVector = tileVector;
	this->window = window;
	this->skeletonVector = skeletonVector;
}

Tile::Tile(float& x, float& y)
	:SPRITE_SIZE(24.f), POSITION_SCALAR(24.f), SCALE(1.5),
	START_TILE(1), DOWN_TILE(2), UP_TILE(3), UP_AND_DOWN_TILE(4), DOOR_TILE(5)
{
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
				tileVector->push_back(Tile(x, y));
			}
			else if (color == Color(0, 255, 0, 255)) {
				y += 8.f;
				skeletonVector->push_back(Skeleton(x, y));
			}
			else if (color == Color(0, 0, 255, 255)) {
				y += 8.f;
				player->sprite.setPosition(x, y);
			}
		}
	}
}

void Tile::draw() {
	for (int i = 0; i < tileVector->size(); i++) {
		window->draw(tileVector->at(i).sprite);
	}
}

void Tile::createLevelPathing(Player* player) {
	this->player = player;
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
	int length = 0;

	switch (templateType) {
	case 0:
		/*length = sizeof(LR_array) / sizeof(LR_array[0]);
		randomPick = rand() % length;*/
		//image = ResourceManager::LR_array[randomPick];
		image = ResourceManager::LR1;
		break;
	case 1:
		/*length = sizeof(DOOR_array) / sizeof(DOOR_array[0]);
		randomPick = rand() % length;*/
		//image = ResourceManager::DOOR_array[randomPick];
		image = ResourceManager::START1;
		break;
	case 2:
		/*length = sizeof(LRD_array) / sizeof(LRD_array[0]);
		randomPick = rand() % length;*/
		//image = ResourceManager::LRD_array[randomPick];
		image = ResourceManager::LRD1;
		break;
	case 3:
		/*length = sizeof(LRU_array) / sizeof(LRU_array[0]);
		randomPick = rand() % length;*/
		//image = ResourceManager::LRU_array[randomPick];
		image = ResourceManager::LRU1;
		break;
	case 4:
		/*length = sizeof(ALL_array) / sizeof(ALL_array[0]);
		randomPick = rand() % length;*/
		//image = ResourceManager::ALL_array[randomPick];
		image = ResourceManager::ALL1;
		break;
	case 5:
		/*length = sizeof(LR_array) / sizeof(LR_array[0]);
		randomPick = rand() % length;*/
		//image = ResourceManager::LR_array[randomPick];
		image = ResourceManager::LR1;
		break;
	default:
		/*length = sizeof(LR_array) / sizeof(LR_array[0]);
		randomPick = rand() % length;*/
		//ResourceManager::LR_array[randomPick];
		image = ResourceManager::LR1;
	}

	if (rand() % 2 == 1) image.flipHorizontally();

	return image;

}

