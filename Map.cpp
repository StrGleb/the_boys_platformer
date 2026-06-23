#include "Map.h"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

Map::Map() {
    mTileSize = 40.f;

    fs::path assetsPath = "assets";

    if (!fs::exists(assetsPath)) {
        if (fs::exists("../assets")) {
            assetsPath = "../assets";
        } 
        else {
            std::cerr << "Папка assets не найдена!\n";
        }
    }

    if (!mTextures['1'].loadFromFile((assetsPath / "asfalt.png").string())) {
        std::cerr << "Не удалось загрузить asfalt.png\n";
    }
    if (!mTextures['2'].loadFromFile((assetsPath / "kamen_kirpich.png").string())) {
        std::cerr << "Не удалось загрузить kamen_kirpich.png\n";
    }
    if (!mTextures['4'].loadFromFile((assetsPath / "ship.png").string())) {
        std::cerr << "Не удалось загрузить ship.png\n";
    }
    if (!mTextures['5'].loadFromFile((assetsPath / "gorod.png").string())) {
        std::cerr << "Не удалось загрузить gorod.png\n";
    }
}

void Map::loadFromFile(const std::string& filename) {
    mGrid.clear();
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Не удалось открыть файл карты: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (!line.empty() && line.back() == '\n') {
            line.pop_back();
        }

        mGrid.push_back(line);
    }
    
    file.close();
}

void Map::draw(sf::RenderWindow& window) {
    for (size_t row = 0; row < mGrid.size(); ++row) {
        for (size_t col = 0; col < mGrid[row].size(); ++col) {
            char tileType = mGrid[row][col];

            if (mTextures.count(tileType)) {
                sf::Sprite tileSprite(mTextures.at(tileType));
                tileSprite.setPosition({col * mTileSize, row * mTileSize});
                window.draw(tileSprite);
            }
        }
    }
}

size_t Map::getRowCount() const { return mGrid.size(); }
size_t Map::getColCount() const { return mGrid.empty() ? 0 : mGrid[0].size(); }
float Map::getTileSize() const { return mTileSize; }

char Map::getTileAt(size_t row, size_t col) const {
    if (row < mGrid.size() && col < mGrid[row].size()) {
        return mGrid[row][col];
    }
    return '0';
}
