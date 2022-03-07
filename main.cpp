#include "Common.h"
#include "Player.h"
#include "Tile.h"
#include "Skeleton.h"
#include "ResourceManager.h"
#include "Game.h"

int main(){
    srand(static_cast<unsigned int>(time(NULL)));
    ResourceManager::loadMedia();

    Game::setup();
    Player::init();
    Game::loadLevel();

    while (Game::window.isOpen()){
        Event event;

        while (Game::window.pollEvent(event)){

            if (event.type == Event::Closed) {
                Game::window.close();
            }
            else if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::W) {
                    Player::jumpCounter = 0;
                }
            }
        }
        Game::window.clear(Color::White);
        Game::window.setView(Game::view);
 
        Tile::draw();
        Skeleton::draw();
        Player::draw();

        Game::window.display();

        Skeleton::update();
        Player::update();
    }

    return 0;
}