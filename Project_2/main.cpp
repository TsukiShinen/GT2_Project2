#include <SFML/Graphics.hpp>
#include <iostream>

#include "ParticleSystem.h"
#include "Point.h"

#include "TileMap.h"

int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::Clock clock; 
    window.setKeyRepeatEnabled(false);

    TileMap tileMap("SandBox2.json");
    sf::View view(tileMap.getStartingPosition().toVector2(), sf::Vector2f(200, 150));

    sf::Vector2f movement = view.getCenter();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::C) {
                    tileMap.changeShowDebug();
                }
            }
        }
        sf::Time deltaTime = clock.restart();

        tileMap.update(deltaTime);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && movement.y > 75) {
            movement.y -= deltaTime.asSeconds() * 50;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            movement.x += deltaTime.asSeconds() * 50;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            movement.y += deltaTime.asSeconds() * 50;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && movement.x > 100) {
            movement.x -= deltaTime.asSeconds() * 50;
        }
        view.setCenter(movement);

        window.clear();
        window.setView(view);
        tileMap.draw(window);
        window.display();
    }

    return 0;
}