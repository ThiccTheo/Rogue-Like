#include "Tile.h"
Tile::Tile(RenderWindow* window, vector<Tile>* tileVector)
	:SRC("Tile/Sprite.png")
{
	texture.loadFromFile(SRC);
	this->tileVector = tileVector;
	this->window = window;
}

Tile::Tile(float &x, float &y, Texture* texture)
{
	this->sprite.setTexture(*texture);
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

	//these do while loops control the start and end placement. The start and ends are always left and right tiles but with special properties
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

	Image door;
	door.loadFromFile("Image/DoorTest.png");

	Image zero;
	zero.loadFromFile("Image/ZeroTest.png");

	Image one1;
	one1.loadFromFile("Image/OneTest.png");

	Image two1;
	two1.loadFromFile("Image/TwoTest.png");

	Image three1;
	three1.loadFromFile("Image/ThreeTest.png");

	//for now, I'm only using one image for each template
	if (templateType == 0) {
		image = zero;
	}
	else if (templateType == 1) {
		image = door;
	}
	else if (templateType == 2) {
		image = one1;
	}
	else if (templateType == 3){
		image = two1;
	}
	else if (templateType == 4){
		image = three1;
	}
	else if (templateType == 5) {
		image = zero;
	}

	return image;

}

