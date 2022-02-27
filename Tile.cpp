#include "Tile.h"
Tile::Tile(RenderWindow* window, vector<Tile>* tileVector)
	:SRC("Tile/Sprite.png"), SPRITE_SIZE(16.f), POSITION_SCALAR(16.f),
	START_TILE(1), DOWN_TILE(2), UP_TILE(3), UP_AND_DOWN_TILE(4), DOOR_TILE(5)
{
	texture.loadFromFile(SRC);
	this->tileVector = tileVector;
	this->window = window;
}

Tile::Tile(float &x, float &y, Texture* texture)
	:SRC("Tile/Sprite.png"), SPRITE_SIZE(16.f), POSITION_SCALAR(16.f),
	START_TILE(1), DOWN_TILE(2), UP_TILE(3), UP_AND_DOWN_TILE(4), DOOR_TILE(5)
{
	this->sprite.setTexture(*texture);
	this->sprite.setOrigin(SPRITE_SIZE / 2, 0.f);
	this->sprite.setPosition(x, y);
}

void Tile::initTiles(int &levelPosX, int& levelPosY, Image* image) {
	Color color;

	float x = 0.f, y = 0.f;
	for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 10; j++) {
			x = POSITION_SCALAR * (j + (10 * levelPosX));
			y = POSITION_SCALAR * (i + (8 * levelPosY));

			color = image->getPixel(j, i);

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
			initTiles(j, i, &image);
		}
		cout << endl;
	}
}

Image Tile::getRoomTemplate(int& templateType) {

	Image image;
	int randomPick = 0;

	/*----------------------------------------*/

	Image door_1;
	door_1.loadFromFile("Image/DoorTest.png");

	Image door_array[] = {door_1,};

	/*----------------------------------------*/

	Image left_right_1;
	left_right_1.loadFromFile("Image/ZeroTest.png");

	Image left_right_array[] = {left_right_1,};

	/*----------------------------------------*/

	Image left_right_down_1;
	left_right_down_1.loadFromFile("Image/OneTest.png");

	Image left_right_down_array[] = {left_right_down_1,};

	/*----------------------------------------*/

	Image left_right_up_1;
	left_right_up_1.loadFromFile("Image/TwoTest.png");

	Image left_right_up_array[] = {left_right_up_1};

	/*----------------------------------------*/

	Image all_1;
	all_1.loadFromFile("Image/ThreeTest.png");

	Image all_array[] = {all_1,};

	/*----------------------------------------*/

	switch(templateType) {
		case 0: image = left_right_array[randomPick]; break;
		case 1: image = door_array[randomPick]; break;
		case 2: image = left_right_down_array[randomPick]; break;
		case 3: image = left_right_up_array[randomPick]; break;
		case 4: image = all_array[randomPick]; break;
		case 5: image = left_right_1; break;
		default: left_right_array[randomPick];
	}

	return image;

}

