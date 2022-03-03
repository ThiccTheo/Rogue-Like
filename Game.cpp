#include "Game.h"

RenderWindow Game::window;
View Game::view;

const float Game::WIDTH = 320.f;
const float Game::HEIGHT = 240.f;

void Game::setup() {
	window.create(VideoMode(WIDTH, HEIGHT), "Rouge Like", Style::Default);
	window.setFramerateLimit(120);
	view.setSize(WIDTH, HEIGHT);
}