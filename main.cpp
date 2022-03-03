#include "Common.h"
#include "Player.h"
#include "Tile.h"
#include "Skeleton.h"

int main(){
    srand(time(0));
    ResourceManager::loadMedia();

    Vector2u resolution(320, 240);
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Rouge Like", Style::Default);
    window.setFramerateLimit(120);

    View view;
    view.setSize(resolution.x, resolution.y);

    vector<Skeleton> skeletonVector;
    Skeleton skeleton(&window, &skeletonVector);

    vector<Tile> tileVector;
    Tile tile(&window, &tileVector, &skeletonVector);
    skeleton.getTileVector(&tileVector);

    Player player(&window, &view, &tileVector);

    tile.createLevelPathing(&player);

    while (window.isOpen()){
        Event event;

        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::W) {
                    player.jumpCounter = 0;
                }
            }
        }
        window.clear(Color::White);
        window.setView(view);
        skeleton.draw();
        player.draw();
        tile.draw();
        window.display();
        //skeleton.update();
        player.update();
    }

    return 0;
}