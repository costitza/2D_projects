#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sprite Example");
    window.setFramerateLimit(60);

    Player player(400.f, 300.f);
    sf::Clock clock;


    sf::RectangleShape hitboxDebug;
    hitboxDebug.setFillColor(sf::Color::Transparent);
    hitboxDebug.setOutlineColor(sf::Color::Red);
    hitboxDebug.setOutlineThickness(1.f);



    // std::cout << texture.getSize().x << "x" << texture.getSize().y << std::endl;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();
        player.update(deltaTime);


        sf::FloatRect playerBounds = player.getGlobalBounds();
        hitboxDebug.setSize(sf::Vector2f(playerBounds.width, playerBounds.height));
        hitboxDebug.setPosition(playerBounds.left, playerBounds.top);


        window.clear(sf::Color::Black);
        window.draw(hitboxDebug);
        player.draw(window);
        window.display();
    }

    return 0;
}
