#include "Common.h"
#include "Player.h"
#include "Tile.h"

int main(){
    srand(time(NULL));

    Vector2u resolution(320, 240);
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Rouge Like", Style::Default);
    window.setFramerateLimit(120);

    View view;
    view.setSize(resolution.x, resolution.y);
    
    vector<Tile> tileVector;
    Tile tile(&window, &tileVector);

    Player player(&window, "Player/sprite.png", &view, &tileVector);

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
        tile.draw();
        window.display();
        player.update();
    }

    return 0;
}