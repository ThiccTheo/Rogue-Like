#include "Tile.h"
Tile::Tile(RenderWindow* window, vector<Tile>* tileVector)
	:SRC("Tile/Sprite.png"), SPRITE_SIZE(24.f), POSITION_SCALAR(24.f),
	START_TILE(1), DOWN_TILE(2), UP_TILE(3), UP_AND_DOWN_TILE(4), DOOR_TILE(5)
{
	texture.loadFromFile(SRC);
	this->tileVector = tileVector;
	this->window = window;
}

Tile::Tile(float &x, float &y, Texture* texture)
	:SRC("Tile/Sprite.png"), SPRITE_SIZE(24.f), POSITION_SCALAR(24.f),
	START_TILE(1), DOWN_TILE(2), UP_TILE(3), UP_AND_DOWN_TILE(4), DOOR_TILE(5)
{
	this->sprite.setScale(1.5, 1.5);
	this->sprite.setTexture(*texture);
	this->sprite.setOrigin(SPRITE_SIZE / 2, 0.f);
	this->sprite.setPosition(x, y);
}

void Tile::initTiles(int &levelPosX, int& levelPosY, const Image& image) {
	Color color;

	float x = 0.f, y = 0.f;
	for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
			x = POSITION_SCALAR * (j + (10 * levelPosX));
			y = POSITION_SCALAR * (i + (8 * levelPosY));

			color = image.getPixel(j, i);

			if (color == Color::Red) {
				tileVector->push_back(Tile(x, y, &texture));
			}
			else if (color == Color::Blue) {
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

	/*----------------------------------------*/

	Image DOOR1;
	DOOR1.loadFromFile("Image/DOOR_Test.png");

	Image DOOR_array[] = {DOOR1,};

	/*----------------------------------------*/

	Image LR1;
	LR1.loadFromFile("Image/LR_Test.png");

	Image LR_array[] = {LR1,};

	/*----------------------------------------*/

	Image LRD1;
	LRD1.loadFromFile("Image/LRD_Test.png");

	Image LRD_array[] = {LRD1,};

	/*----------------------------------------*/

	Image LRU1;
	LRU1.loadFromFile("Image/LRU_Test.png");

	Image LRU_array[] = {LRU1};

	/*----------------------------------------*/

	Image ALL1;
	ALL1.loadFromFile("Image/ALL_Test.png");

	Image ALL_array[] = {ALL1,};

	/*----------------------------------------*/

	switch (templateType) {
		case 0: 
			length = sizeof(LR_array) / sizeof(LR_array[0]);
			randomPick = rand() % length;
			image = LR_array[randomPick]; 
			break;
		case 1: 
			length = sizeof(DOOR_array) / sizeof(DOOR_array[0]);
			randomPick = rand() % length;
			image = DOOR_array[randomPick];
			break;
		case 2: 
			length = sizeof(LRD_array) / sizeof(LRD_array[0]);
			randomPick = rand() % length;
			image = LRD_array[randomPick];
			break;
		case 3:
			length = sizeof(LRU_array) / sizeof(LRU_array[0]);
			randomPick = rand() % length;
			image = LRU_array[randomPick];
			break;
		case 4:
			length = sizeof(ALL_array) / sizeof(ALL_array[0]);
			randomPick = rand() % length;
			image = ALL_array[randomPick];
			break;
		case 5:
			length = sizeof(LR_array) / sizeof(LR_array[0]);
			randomPick = rand() % length;
			image = LR_array[randomPick];
			break;
		default: 
			length = sizeof(LR_array) / sizeof(LR_array[0]);
			randomPick = rand() % length;
			LR_array[randomPick];
	}
	
	if(rand() % 2 == 1) image.flipHorizontally();

	return image;

}

