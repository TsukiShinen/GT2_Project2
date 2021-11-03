#include <SFML/Graphics.hpp>
#include <iostream>

#include "ParticleSystem.h"
#include "TileMap.h"



int main()
{

    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    sf::Clock clock; 
    window.setKeyRepeatEnabled(false);

    TileMap tileMap("SandBox.json");


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


        window.clear();
        tileMap.draw(window);
        window.display();
    }

    return 0;
}