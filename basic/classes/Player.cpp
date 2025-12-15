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
    gravity = 980.f;
    velocity = sf::Vector2f(0.f, 0.f);
    jumpStrength = 450.f;
    isOnGround = false;
    animationTimer = 0.f;
    timePerFrame = 0.3f;

}

void Player::handleCollisions(const std::vector<sf::RectangleShape>& solids) {
    isOnGround = false;

    for (const auto& solid : solids) {
        // 1. Get Bounds
        sf::FloatRect playerBounds = sprite.getGlobalBounds();
        sf::FloatRect solidBounds = solid.getGlobalBounds();

        // 2. Check Intersection
        if (playerBounds.intersects(solidBounds)) {
            
            // 3. Calculate Overlap on both axes
            // (How deep are we inside the block?)
            float bottom = playerBounds.top + playerBounds.height;
            float right = playerBounds.left + playerBounds.width;
            float solidBottom = solidBounds.top + solidBounds.height;
            float solidRight = solidBounds.left + solidBounds.width;

            float overlapLeft = right - solidBounds.left;
            float overlapRight = solidRight - playerBounds.left;
            float overlapTop = bottom - solidBounds.top;
            float overlapBottom = solidBottom - playerBounds.top;

            // Find the smallest overlap to decide which way to push
            float minOverlapX = std::min(overlapLeft, overlapRight);
            float minOverlapY = std::min(overlapTop, overlapBottom);

            // 4. Resolve the Collision
            if (minOverlapX < minOverlapY) {
                // X Collision (Horizontal)
                // We are penetrating less on X, so it's a Wall hit
                if (overlapLeft < overlapRight) {
                    // Hit left side of wall -> Push Left
                    sprite.move(-overlapLeft, 0.f);
                } else {
                    // Hit right side of wall -> Push Right
                    sprite.move(overlapRight, 0.f);
                }
                
                // Note: We do NOT stop Y velocity here
            } 
            else {
                // Y Collision (Vertical)
                // We are penetrating less on Y, so it's a Floor/Ceiling hit
                if (overlapTop < overlapBottom) {
                    // Hit Top (Floor) -> Push Up
                    sprite.move(0.f, -overlapTop);
                    velocity.y = 0.f; // Stop falling
                    isOnGround = true;
                } else {
                    // Hit Bottom (Ceiling) -> Push Down
                    sprite.move(0.f, overlapBottom);
                    velocity.y = 0.f; // Stop jumping
                }
            }
        }
    }
}


sf::FloatRect Player::getGlobalBounds() {
    return sprite.getGlobalBounds();
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Player::update(float deltaTime, std::vector<sf::RectangleShape> solids) {

    velocity.y += gravity * deltaTime; // apply gravity
    velocity.x = 0.f; // reset horizontal velocity each frame

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocity.x = -speed;
        sprite.setScale(-1.f, 1.f);

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocity.x = speed;
        sprite.setScale(1.f, 1.f);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isOnGround){
        velocity.y = -jumpStrength;
        isOnGround = false;
    }


    sprite.move(velocity * deltaTime);
    handleCollisions(solids);


    if (velocity.x != 0 && isOnGround) {
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