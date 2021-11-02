#include <SFML/Graphics.hpp>
#include <iostream>

#include "ParticleSystem.h"
#include "TileMap.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::Clock clock;

    TileMap tileMap("SandBox.json");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Time deltaTime = clock.restart();


        window.clear();

        window.display();
    }

    return 0;
}