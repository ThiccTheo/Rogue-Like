#include "Common.h"
#include "Player.h"
#include "Tile.h"

int main(){
    srand(time(NULL));
    Clock dtClock;
    float deltaTime = 0.f;
    Vector2u resolution(320, 240);
    RenderWindow window(VideoMode(resolution.x, resolution.y), "Rouge Like", Style::Default);
    window.setFramerateLimit(120);

    View view;
    view.setSize(resolution.x, resolution.y);
    
    vector<Tile> tileVector;
    Tile tile(&window, &tileVector);

    Player player(&window, "Player/sprite.png", &deltaTime, &view, &tileVector);

    tile.createLevelPathing(&player);

    while (window.isOpen()){
        Event event;

        while (window.pollEvent(event)){
            if (event.type == Event::Closed)
                window.close();
        }
        
        deltaTime = dtClock.restart().asSeconds();
        //cout << 1.f / deltaTime << endl;
        window.clear(Color::White);
        window.setView(view);
        player.draw();
        tile.draw();
        window.display();
        player.update();
    }

    return 0;
}