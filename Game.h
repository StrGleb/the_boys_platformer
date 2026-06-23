#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

#include "Player.h"
#include "Map.h"

class Game {
    sf::RenderWindow mWindow;
    Player mPlayer;
    Map mMap;
    sf::View mView; // камера следования
    sf::Texture mCityTexture;
    std::optional<sf::Sprite> mCitySprite;
    float mParallaxFactor = 0.3f;

public:
    Game();
    void run();
    void processEvents();
    void update();
    void render();
};    
