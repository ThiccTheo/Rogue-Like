#include "Game.h"

RenderWindow Game::window;
View Game::view;
RectangleShape Game::cullingPoint;

const float Game::WIDTH = 400.f;
const float Game::HEIGHT = 250.f;

void Game::setup() {
	window.create(VideoMode(static_cast<unsigned int>(WIDTH), static_cast<unsigned int>(HEIGHT)), "Rouge Like", Style::Default);
	window.setFramerateLimit(120);
	view.setSize(WIDTH, HEIGHT);
	cullingPoint.setSize(Vector2f(WIDTH, HEIGHT));
	cullingPoint.setFillColor(Color::Red);
	cullingPoint.setOrigin(cullingPoint.getSize().x / 2.f, cullingPoint.getSize().y / 2.f);
}

void Game::loadLevel() {
	Tile::tileVector.clear();
	Skeleton::skeletonVector.clear();
	Chest::chestVector.clear();
	cout << "\033[H\033[J";
	Tile::setupBackground();
	Tile::createLevelPathing();
}