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
    float animationTimer;
    float timePerFrame;
    float gravity;
    sf::Vector2f velocity;
    bool isOnGround;
    float jumpStrength;
    void handleCollisions(const std::vector<sf::RectangleShape>& solids);

public:
    Player(float x, float y);

    void update(float deltaTime, std::vector<sf::RectangleShape> solids);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getGlobalBounds();

};