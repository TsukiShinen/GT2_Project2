#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Point.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    srand(time(NULL));
    sf::Clock clock; 
    window.setKeyRepeatEnabled(false);

    Game game(Point(800, 600));
    game.load();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                game.keypressed(event.key.code);
            }
        }
        sf::Time deltaTime = clock.restart();
        game.update(deltaTime);

        window.clear();
        game.draw(window);
        window.display();
    }

    return 0;
}