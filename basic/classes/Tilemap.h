#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Tilemap {
private:
    std::vector<sf::RectangleShape> tiles;
    sf::Texture groundTexture;


    float tileSize;

public:
    Tilemap(float size);

    void loadMap(const std::vector<std::vector<int>>& mapData);
    void draw(sf::RenderWindow& window);

    const std::vector<sf::RectangleShape>& getSolids() const {
        return tiles;
    }


};