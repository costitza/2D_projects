#include "Player.h"
#include <iostream>

Player::Player(float x, float y) {


    if(!texture.loadFromFile("rsc/character_transformationmotion.png")){
        std::cerr << "Error loading player texture!" << std::endl;
    }

    sprite.setTexture(texture);

    int frameW = 160;
    int frameH = 280;

    frames.push_back(sf::IntRect(80, 20, frameW, frameH));
    frames.push_back(sf::IntRect(80, 40 + frameH, frameW, frameH));

    currentFrameIndex = 0;
    sprite.setTextureRect(frames[currentFrameIndex]);
    sprite.setPosition(x, y);

    sprite.setOrigin(frameW / 2.f, frameH / 2.f);

    speed = 200.f;
    isMoving = false;
    animationTimer = 0.f;

}

sf::FloatRect Player::getGlobalBounds() {
    return sprite.getGlobalBounds();
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::update(float deltaTime){
    isMoving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprite.move(-speed * deltaTime, 0);
        isMoving = true;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite.move(speed * deltaTime, 0);
        isMoving = true;
    }

    if (isMoving) {
        animationTimer += deltaTime;
        if (animationTimer >= timePerFrame) {
            currentFrameIndex = (currentFrameIndex + 1) % frames.size();
            sprite.setTextureRect(frames[currentFrameIndex]);
            animationTimer = 0.f;
        }
    } else {
        currentFrameIndex = 0;
        sprite.setTextureRect(frames[currentFrameIndex]);
        animationTimer = 0.f;
    }
}