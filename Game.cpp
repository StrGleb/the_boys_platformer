#include "Game.h"
#include <optional>
#include <stdexcept>

Game::Game() {
    mWindow.create(sf::VideoMode({800, 600}), "The Boys: Platformer");
    mWindow.setFramerateLimit(60); 
    mMap.loadFromFile("level.txt");
    mView.setSize({800.f, 600.f});
    mView.setCenter({400.f, 300.f});

    if (!mCityTexture.loadFromFile("assets/gorod.png")) {
        throw std::runtime_error("Missing gorod.png");
    }

    mCityTexture.setRepeated(true);
    mCitySprite.emplace(mCityTexture);
    mCitySprite->setPosition({0.f, 0.f});
    mCitySprite->setTextureRect(sf::IntRect({0, 0}, {800, 259}));
    mCitySprite->setScale({1.85f, 1.85f});
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

        // КНОПКИ МЫШИ НАЖАТЫ: Включаем флаги движения и прыжка
        if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            // ЛКМ -> Бег влево
            if (mousePressed->button == sf::Mouse::Button::Left) {
                mPlayer.setMovingLeft(true);
            }
            // ПКМ -> Бег вправо
            if (mousePressed->button == sf::Mouse::Button::Right) {
                mPlayer.setMovingRight(true);
            }
            // Нажатие колесика (Middle) -> Прыжок
            if (mousePressed->button == sf::Mouse::Button::Middle) {
                mPlayer.setJumping(true);
            }
        }

        // КНОПКИ МЫШИ ОТПУЩЕНЫ: Выключаем флаги движения и прыжка
        if (const auto* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>()) {
            // Отпустили ЛКМ -> Стоп влево
            if (mouseReleased->button == sf::Mouse::Button::Left) {
                mPlayer.setMovingLeft(false);
            }
            // Отпустили ПКМ -> Стоп вправо
            if (mouseReleased->button == sf::Mouse::Button::Right) {
                mPlayer.setMovingRight(false);
            }
            // Отпустили колесико -> Сброс флага прыжка
            if (mouseReleased->button == sf::Mouse::Button::Middle) {
                mPlayer.setJumping(false);
            }
        }
    }
}

void Game::update() {
    // Просто обновляем логику игрока (мышь теперь опрашивается строго через события выше)
    mPlayer.update(mMap);
    
    // Камера плавно центрируется по игроку
    sf::Vector2f playerPos = mPlayer.getPosition();
    mView.setCenter({playerPos.x, 300.f}); 
    mWindow.setView(mView);

    const float viewWidth = mView.getSize().x;
    const float viewLeft = mView.getCenter().x - (viewWidth / 2.f);
    const int textureOffsetX = static_cast<int>(viewLeft * mParallaxFactor);

    if (mCitySprite) {
        mCitySprite->setPosition({viewLeft, 0.f});
        mCitySprite->setTextureRect(sf::IntRect({textureOffsetX, 0}, {static_cast<int>(viewWidth) + 1, 259}));
    }
}

void Game::render() {
    mWindow.clear(sf::Color::Black);
    if (mCitySprite) {
        mWindow.draw(*mCitySprite);
    }
    mMap.draw(mWindow);
    mPlayer.draw(mWindow);
    mWindow.display();
}
