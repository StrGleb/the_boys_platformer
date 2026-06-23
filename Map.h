#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>

class Map {
    std::vector<std::string> mGrid;
    float mTileSize;

    std::map<char, sf::Texture> mTextures; 

public:
    Map();
    void loadFromFile(const std::string& filename);
    void draw(sf::RenderWindow& window);

    char getTileAt(size_t row, size_t col) const;
    size_t getRowCount() const;
    size_t getColCount() const;
    float getTileSize() const;
};
