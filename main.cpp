#include "Common.h"
#include "Player.h"
#include "Tile.h"
#include "Enemy.h"

int main(){
    srand(time(0));

    Vector2u resolution(320, 240);
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Rouge Like", Style::Default);
    window.setFramerateLimit(120);

    View view;
    view.setSize(resolution.x, resolution.y);
    
    vector<Tile> tileVector;
    Tile tile(&window, &tileVector);

    Player player(&window, "Player/sprite.png", &view, &tileVector);

    vector<Skeleton> skeletonVector;
    Skeleton skeleton(&window, &skeletonVector, "Skeleton/sprite.png");
    skeletonVector.push_back(skeleton);

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
        player.draw();
        skeleton.draw();
        tile.draw();
        window.display();
        player.update();
    }

    return 0;
}