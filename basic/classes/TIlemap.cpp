#include "Tilemap.h"
#include <iostream>


Tilemap::Tilemap(float size){
    tileSize = size;

    if (!groundTexture.loadFromFile("rsc/PNG/Platformer/Ground_11.png")) {
        std::cerr << "Error loading ground texture!" << std::endl;
    }
}


void Tilemap::loadMap(const std::vector<std::vector<int>>& mapData){
    tiles.clear();
    for (size_t row = 0; row < mapData.size(); ++row) {
        for (size_t col = 0; col < mapData[row].size(); ++col) {
            if (mapData[row][col] == 1) { // Assuming 1 represents a tile
                sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
                tile.setPosition(col * tileSize, row * tileSize);
                tile.setTexture(&groundTexture); // Example color
                tiles.push_back(tile);
            }
        }
    }
}

void Tilemap::draw(sf::RenderWindow& window){
    for (const auto& tile : tiles) {
        window.draw(tile);
    }
}
