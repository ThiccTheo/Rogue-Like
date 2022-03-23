#include "Common.h"
#include "Player.h"
#include "Tile.h"
#include "Skeleton.h"
#include "ResourceManager.h"
#include "Game.h"
#include "GUI.h"
#include "Chest.h"
#include "Sword.h"
#include "Slime.h"

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
	Slime::slimeVector.clear();
	cout << "\033[H\033[J";
	Tile::setupBackground();
	Tile::createLevelPathing();
}

void Game::run() {
    srand(static_cast<unsigned int>(time(NULL)));
    ResourceManager::loadMedia();

    setup();
    GUI::init();
    Player::init();
    Sword::init();
    loadLevel();

    while (window.isOpen()) {
        Event event;

        while (window.pollEvent(event)) {

            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::W) {
                    Player::jumpCounter = 0;
                }
            }
            if (event.type == Event::MouseButtonReleased) {
                if (event.mouseButton.button == Mouse::Left) {
                    Sword::clickCounter = 0;
                }
            }
        }

        window.clear(Color::White);
        window.setView(Game::view);

        Tile::draw();
        Chest::draw();
        Skeleton::draw();
        Slime::draw();
        Sword::draw();
        Player::draw();
        GUI::draw();

        window.display();

        Skeleton::update();
        Slime::update();
        Player::update();
        Sword::update();

    }
}