#include "Player.h"
#include <iostream>
#include <cmath>

//
//Player::Player(std::pair<int, int> size) {
//    _sprite._size = size;
//    _sprite._rect.setFillColor(sf::Color::White);
//    _sprite._rect.setPosition(_position);
//}



void Player::update(sf::Time clock, std::vector<sf::RectangleShape>& listOfElements) {
    _direction = { 0.f, 0.f };
    float speed = _speed * clock.asSeconds();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        // move(0, -_speed*clock.asSeconds());
        _direction.y = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        // move(_speed * clock.asSeconds(), 0);
        _direction.x = speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        // move(0, _speed*clock.asSeconds());
        _direction.y = speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        // move(-_speed*clock.asSeconds(), 0);
        _direction.x = -speed;
    }

    if (_direction.x != 0.f && _direction.y != 0.f) {
        float ratio = speed / std::sqrtf(2);
        _direction.x *= ratio/speed;
        _direction.y *= ratio / speed;
    }
    
    bool canMove = true;
    for (sf::RectangleShape& thing : listOfElements) {
        if (collides(thing.getPosition())) {
            canMove = false;
        }
    }
    if (canMove) {
        move(_direction.x, _direction.y);
    }
}

bool Player::collides(sf::Vector2f element) {
    sf::FloatRect boundings = this->getGlobalBounds();
    if (boundings.contains(element)) {
        std::cout << "e";
        return true;
    }
    return false;
};
