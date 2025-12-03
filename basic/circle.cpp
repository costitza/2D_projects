#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(500, 500), "Moving circle!");
    sf::CircleShape circle(50);

    circle.setFillColor(sf::Color::Red);
    circle.setPosition(200, 200);

    bool color_switch = true;

    while (window.isOpen()) {


        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
                color_switch = !color_switch;
            }
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            circle.move(0.1f, 0);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            circle.move(-0.1f, 0);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            circle.move(0, -0.1f);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            circle.move(0, 0.1f);
        }

        // wall collision detection (clamp inside window)
        sf::Vector2f pos = circle.getPosition();
        float radius = circle.getRadius();
        float diameter = radius * 2;
        float winX = window.getSize().x;
        float winY = window.getSize().y;

        if (pos.x < 0)
            circle.setPosition(0, pos.y);

        else if (pos.x + diameter > winX)
            circle.setPosition(winX - diameter, pos.y);

        if (pos.y < 0)
            circle.setPosition(pos.x, 0);

        else if (pos.y + diameter > winY)
            circle.setPosition(pos.x, winY - diameter);

        window.clear(color_switch ? sf::Color::Blue : sf::Color::Green);
        window.draw(circle);
        window.display();
    }

    return 0;
}
