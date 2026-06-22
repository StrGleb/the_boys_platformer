#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Map {
    std::vector<std::string> mGrid;
    sf::RectangleShape mTile;
    float mTileSize;

public:
    Map();
    void loadFromFile(const std::string& filename);
    void draw(sf::RenderWindow& window);

    char getTileAt(size_t row, size_t col) const;
    size_t getRowCount() const;
    size_t getColCount() const;
    float getTileSize() const;
};