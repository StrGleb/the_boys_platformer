#include "Player.h"
#include "Map.h"

Player::Player() {
    mShape.setSize({40.f, 60.f});
    mShape.setFillColor(sf::Color::Red);
    mShape.setPosition({100.f, 40.f});
    mSpeed = 5.f;
    mVelocityY = 0.f;
    mIsGrounded = false;
}

void Player::update(const Map& map) {
    // ГОРИЗОНТАЛЬНОЕ ДВИЖЕНИЕ (флаги Game)
    float moveX = 0.f;
    if (mIsMovingLeft)  moveX -= mSpeed;
    if (mIsMovingRight) moveX += mSpeed;

    mShape.move({moveX, 0.f});

    float tileSize = map.getTileSize();
    sf::FloatRect playerBounds = mShape.getGlobalBounds();

    // Строгая проверка боковых столкновений (игнорируем пол под ногами)
    int startRow = static_cast<int>((playerBounds.position.y + 1.f) / tileSize);
    int endRow = static_cast<int>((playerBounds.position.y + playerBounds.size.y - 1.f) / tileSize);
    int startCol = static_cast<int>(playerBounds.position.x / tileSize) - 1;
    int endCol = static_cast<int>((playerBounds.position.x + playerBounds.size.x) / tileSize) + 1;

    if (startRow < 0) startRow = 0;
    if (endRow >= static_cast<int>(map.getRowCount())) endRow = map.getRowCount() - 1;
    if (startCol < 0) startCol = 0;
    if (endCol >= static_cast<int>(map.getColCount())) endCol = map.getColCount() - 1;

    for (int row = startRow; row <= endRow; ++row) {
        for (int col = startCol; col <= endCol; ++col) {
            if (map.getTileAt(row, col) == '1' || map.getTileAt(row, col) == '2') {
                sf::FloatRect tileBounds({col * tileSize, row * tileSize}, {tileSize, tileSize});
                if (auto intersection = playerBounds.findIntersection(tileBounds)) {
                    if (moveX > 0.f) mShape.move({-intersection->size.x, 0.f});
                    if (moveX < 0.f) mShape.move({intersection->size.x, 0.f});
                    playerBounds = mShape.getGlobalBounds();
                }
            }
        }
    }

    // 2. ВЕРТИКАЛЬНОЕ ДВИЖЕНИЕ 
    if (!mIsGrounded) {
        mVelocityY += 0.5f;
    } else {
        mVelocityY = 0.f;
    }

    mShape.move({0.f, mVelocityY}); 
    playerBounds = mShape.getGlobalBounds();
    mIsGrounded = false;

    // Полный пересчет квадрата блоков для оси Y
    startRow = static_cast<int>(playerBounds.position.y / tileSize) - 1;
    endRow = static_cast<int>((playerBounds.position.y + playerBounds.size.y) / tileSize) + 1;
    startCol = static_cast<int>(playerBounds.position.x / tileSize) - 1;
    endCol = static_cast<int>((playerBounds.position.x + playerBounds.size.x) / tileSize) + 1;

    if (startRow < 0) startRow = 0;
    if (endRow >= static_cast<int>(map.getRowCount())) endRow = map.getRowCount() - 1;
    if (startCol < 0) startCol = 0;
    if (endCol >= static_cast<int>(map.getColCount())) endCol = map.getColCount() - 1;

    for (int row = startRow; row <= endRow; ++row) {
        for (int col = startCol; col <= endCol; ++col) {
            if (map.getTileAt(row, col) == '1' || map.getTileAt(row, col) == '2') {
                sf::FloatRect tileBounds({col * tileSize, row * tileSize}, {tileSize, tileSize});
                if (auto intersection = playerBounds.findIntersection(tileBounds)) {
                    if (mVelocityY > 0.f) {
                        mShape.move({0.f, -intersection->size.y - 0.05f}); // зазор, чтобы гг не застрял при выталкивании
                        mIsGrounded = true;
                        mVelocityY = 0.f;
                    } else if (mVelocityY < 0.f) {
                        mShape.move({0.f, intersection->size.y});
                        mVelocityY = 0.f;
                    }
                    playerBounds = mShape.getGlobalBounds();
                }
            }
        }
    }
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(mShape);
}
