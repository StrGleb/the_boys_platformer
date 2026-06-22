#include "Game.h"
#include <optional>

Game::Game() {
    mWindow.create(sf::VideoMode({800, 600}), "The Boys: Platformer");
    mWindow.setFramerateLimit(60); 
    mMap.loadFromFile("level.txt");
    mView.setSize({800.f, 600.f});
}

void Game::run() {
    while (mWindow.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    while (const std::optional event = mWindow.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            mWindow.close();
        }

        // нажатие клавиш
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::A) mPlayer.setMovingLeft(true);
            if (keyPressed->code == sf::Keyboard::Key::D) mPlayer.setMovingRight(true);
            if (keyPressed->code == sf::Keyboard::Key::W) mPlayer.jump();
        }

        // отжатие клавиш
        if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>()) {
            if (keyReleased->code == sf::Keyboard::Key::A) mPlayer.setMovingLeft(false);
            if (keyReleased->code == sf::Keyboard::Key::D) mPlayer.setMovingRight(false);
        }
    }
}

void Game::update() {
    mPlayer.update(mMap);
    sf::Vector2f playerPos = mPlayer.getPosition();
    mView.setCenter({playerPos.x, 300.f});
    mWindow.setView(mView); // отображение игрового мира через камеру
}

void Game::render() {
    mWindow.clear(sf::Color::Blue);
    mMap.draw(mWindow);
    mPlayer.draw(mWindow);
    mWindow.display();
}
