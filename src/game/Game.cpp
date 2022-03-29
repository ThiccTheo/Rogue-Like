#include "../player/Player.h"
#include "../tile/Tile.h"
#include "../entity/skeleton/Skeleton.h"
#include "../resource/ResourceManager.h"
#include "../game/Game.h"
#include "../gui/GUI.h"
#include "../chest/Chest.h"
#include "../weapon/sword/Sword.h"
#include "../entity/slime/Slime.h"
#include "../boss/paladin/Paladin.h"

RenderWindow Game::window;
View Game::view;
RectangleShape Game::cullingPoint;

const float Game::WIDTH = 400.f;
const float Game::HEIGHT = 250.f;

int Game::currentLevel = 3;

void Game::setup() {
	window.create(VideoMode(static_cast<unsigned int>(WIDTH), static_cast<unsigned int>(HEIGHT)), "Rouge Like", Style::Default);
	window.setFramerateLimit(120);
	view.setSize(WIDTH, HEIGHT);
	cullingPoint.setSize(Vector2f(WIDTH, HEIGHT));
	cullingPoint.setFillColor(Color::Red);
	cullingPoint.setOrigin(cullingPoint.getSize().x / 2.f, cullingPoint.getSize().y / 2.f);
}

void Game::loadLevel() {
    currentLevel++;
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
        Paladin::draw();
        Sword::draw();
        Player::draw();
        GUI::draw();

        window.display();

        Skeleton::update();
        Slime::update();
        Paladin::update();
        Player::update();
        Sword::update();
    }
}