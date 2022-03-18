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

int main(){
    srand(static_cast<unsigned int>(time(NULL)));
    ResourceManager::loadMedia();

    Game::setup();
    GUI::init();
    Player::init();
    Sword::init();
    Game::loadLevel();

    while (Game::window.isOpen()){
        Event event;

        while (Game::window.pollEvent(event)){

            if (event.type == Event::Closed) {
                Game::window.close();
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

        Game::window.clear(Color::Black);
        Game::window.setView(Game::view);

        Tile::draw();
        Chest::draw();
        Skeleton::draw();
        Slime::draw();
        Sword::draw();
        Player::draw();
        GUI::draw();

        Game::window.display();

        Skeleton::update();
        Slime::update();
        Player::update();
        Sword::update();
        
    }

    return 0;
}