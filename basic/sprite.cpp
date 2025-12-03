#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sprites!");

    int frameW = 160;
    int frameH = 320;

    sf::Texture texture;

    texture.loadFromFile("rsc/character_transformationmotion.png");
    sf::IntRect frameRect(80, 0, frameW + 80, frameH);
    sf::Sprite player(texture, frameRect);
    player.setPosition(200, 200);

    std::cout << texture.getSize().x << "x" << texture.getSize().y << std::endl;


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }




        window.clear(sf::Color::Black);
        window.draw(player);
        window.display();
    }

    return 0;
}
