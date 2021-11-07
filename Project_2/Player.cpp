#include "Player.h"
#include <iostream>
#include <cmath>

//
//Player::Player(std::pair<int, int> size) {
//    _sprite._size = size;
//    _sprite._rect.setFillColor(sf::Color::White);
//    _sprite._rect.setPosition(_position);
//}

void Player::draw(sf::RenderWindow& window) {
    if (_debug) {
        _hitbox.setFillColor(sf::Color::Red);
        _movebox.setFillColor(sf::Color::Green);
        //window.draw(_hitbox);
        window.draw(_movebox);
    }
}

void Player::update(sf::Time clock, std::vector<sf::FloatRect>& listOfElements) {
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
    sf::FloatRect playerPos = this->getGlobalBounds();
    sf::FloatRect futurePos = playerPos;
    
    

   
    

    futurePos.left += 13;
    futurePos.top += 17;
    futurePos.width = 6;
    futurePos.height = 3;

    
    sf::Vector2f initial(_direction.x, _direction.y);
  

    for (const sf::FloatRect& bound : listOfElements) {
        //std::cout << bound.width << std::endl;
        if (_direction.x != 0.f) {
            futurePos.left += _direction.x;
            if (futurePos.intersects(bound)) {
                
                _direction.x = 0.f;
                std::cout << "reset x \n";
            }
            futurePos.left -= initial.x;
        }
        
        if (_direction.y != 0.f) {
            futurePos.top += _direction.y;
            if (futurePos.intersects(bound)) {
                
                _direction.y = 0.f;
                std::cout << "reset y \n";
            }
            futurePos.top -= initial.y;
        }

        if (_direction.x != 0.f && _direction.y != 0.f) {
            futurePos.left += _direction.x;
            futurePos.top += _direction.y;
            if (futurePos.intersects(bound)) {
                _direction.x = 0.f;
                _direction.y = 0.f;
                std::cout << "reset both \n";
            }
            futurePos.left -= initial.x;
            futurePos.top -= initial.y;
        }
       

    }
    
    // adding after verification
    futurePos.left += _direction.x;
    futurePos.top += _direction.y;
    //fixing 32 by 32 hitbox to 8 by 8 texture
    _hitbox.setSize(sf::Vector2f(8, 8));
    _hitbox.setPosition(futurePos.left -1, futurePos.top -5);
    _movebox.setSize(sf::Vector2f(futurePos.width, futurePos.height));
    _movebox.setPosition(futurePos.left, futurePos.top);
    move(_direction);
}



bool Player::collides(sf::FloatRect element) {
    sf::FloatRect boundings = this->getGlobalBounds();
    if (boundings.intersects(element)) {
        return true;
    }
    return false;
};
