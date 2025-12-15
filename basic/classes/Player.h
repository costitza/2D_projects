#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Player {

private:
    sf::Sprite sprite;
    sf::Texture texture;
    std::vector<sf::IntRect> frames;
    int currentFrameIndex;

    float speed;
    bool isMoving;
    float animationTimer;
    float timePerFrame;

public:
    Player(float x, float y);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getGlobalBounds();

};