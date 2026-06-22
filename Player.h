#pragma once

#include <SFML/Graphics.hpp>

class Map;

class Player {
    private: sf::RectangleShape mShape;
    float mSpeed;
    float mVelocityY;
    bool mIsGrounded;
    bool mIsMovingLeft = false;
    bool mIsMovingRight = false;

public:
    Player();

    void update(const Map& map);
    void draw(sf::RenderWindow& window);

    void setMovingLeft(bool move) { mIsMovingLeft = move; }
    void setMovingRight(bool move) { mIsMovingRight = move; }
    void jump() { if (mIsGrounded) { mVelocityY = -12.f; mIsGrounded = false; } }

    sf::Vector2f getPosition() const {return mShape.getPosition(); }
};