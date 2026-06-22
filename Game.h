#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Map.h"

class Game {
    sf::RenderWindow mWindow;
    Player mPlayer;
    Map mMap;
    sf::View mView; // камера следования

public:
    Game();
    void run();
    void processEvents();
    void update();
    void render();
};    