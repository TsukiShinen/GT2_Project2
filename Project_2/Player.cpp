#include "Player.h"

//
//Player::Player(std::pair<int, int> size) {
//    _sprite._size = size;
//    _sprite._rect.setFillColor(sf::Color::White);
//    _sprite._rect.setPosition(_position);
//}

Player::Player() {
    _texture.loadFromFile("./Assets/PlayerAnimations.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(sf::IntRect(0, 352, 32, 32));
    // column starts with 0 as line
    _animCtrl.addAnimation("WalkR", Animation(_animCtrl.getAllRect(336, 4), 0.1f));
    _animCtrl.addAnimation("WalkL", Animation(_animCtrl.getAllRect({ 160, 161, 162, 163 }), 0.3));
    _animCtrl.addAnimation("WalkTR", Animation(_animCtrl.getAllRect({ 160, 161, 162, 163 }), 0.3));
    _animCtrl.addAnimation("WalkTL", Animation(_animCtrl.getAllRect({ 160, 161, 162, 163 }), 0.3));
    _animCtrl.addAnimation("Idle", Animation(_animCtrl.getAllRect(176, 16), 0.5f));
    _animCtrl.changeCurrentAnim("Idle");
}

void Player::draw(sf::RenderWindow& window) {
    if (_debug) {
        _hitbox.setFillColor(sf::Color::Red);
        _movebox.setFillColor(sf::Color::Green);
        window.draw(_hitbox);
        window.draw(_movebox);
    }
    window.draw(_sprite);
}

void Player::changeSprite() {
    if (_direction.x < 0) 
    {
        if (_direction.y < 0) 
        {
            if (_animCtrl.getCurrentAnim() != "WalkTL") {
                _animCtrl.changeCurrentAnim("WalkTL");
            }
                
        }
        else if (_direction.y > 0) 
        {
            if (_animCtrl.getCurrentAnim() != "Idle") {
                _animCtrl.changeCurrentAnim("Idle");
            }
            
        }
        else {
            if (_animCtrl.getCurrentAnim() != "WalkL") {
                _animCtrl.changeCurrentAnim("WalkL");
            }
            
        }
    }
    else if (0 < _direction.x)
    {
        if (_direction.y < 0)
        {
            if (_animCtrl.getCurrentAnim() != "WalkTR") {
                _animCtrl.changeCurrentAnim("WalkTR");
            }
            
        }
        else if (0 < _direction.y)
        {
            if (_animCtrl.getCurrentAnim() != "WalkTR") {
                _animCtrl.changeCurrentAnim("WalkTR");
            }
            
        }
        else {
            if (_animCtrl.getCurrentAnim() != "WalkR") {
                _animCtrl.changeCurrentAnim("WalkR");
            }
        }
    }
    else
    {
        if (_direction.y < 0)
        {
            if (_animCtrl.getCurrentAnim() != "Idle") {
                _animCtrl.changeCurrentAnim("Idle");
            }
            
        }
        else if (_direction.y > 0)
        {
            if (_animCtrl.getCurrentAnim() != "Idle") {
                _animCtrl.changeCurrentAnim("Idle");
            }
            
        }
        else {
            if (_animCtrl.getCurrentAnim() != "Idle") {
                _animCtrl.changeCurrentAnim("Idle");
            }
            
        }
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
    sf::FloatRect playerPos = _sprite.getGlobalBounds();
    sf::FloatRect futurePos = playerPos;
    _animCtrl.update(clock);
    
    _sprite.setTextureRect(_animCtrl.getCurrentRect());
    

   
    

    futurePos.left += 13;
    futurePos.top += 17;
    futurePos.width = 6;
    futurePos.height = 3;

    
    sf::Vector2f initial(_direction.x, _direction.y);
  

    for (const sf::FloatRect& bound : listOfElements) {
        /*sf::FloatRect bound = thing.getGlobalBounds();*/
        
        if (_direction.x != 0.f) {
            futurePos.left += _direction.x;
            if (futurePos.intersects(bound)) {
                
                _direction.x = 0.f;
                // reset x
            }
            futurePos.left -= initial.x;
        }
        
        if (_direction.y != 0.f) {
            futurePos.top += _direction.y;
            if (futurePos.intersects(bound)) {
                
                _direction.y = 0.f;
                // reset y
            }
            futurePos.top -= initial.y;
        }

        if (_direction.x != 0.f && _direction.y != 0.f) {
            futurePos.left += _direction.x;
            futurePos.top += _direction.y;
            if (futurePos.intersects(bound)) {
                _direction.x = 0.f;
                _direction.y = 0.f;
                // reset both 
            }
            futurePos.left -= initial.x;
            futurePos.top -= initial.y;
        }
       

    }
    changeSprite();
    // adding after verification
    futurePos.left += _direction.x;
    futurePos.top += _direction.y;
    //fixing 32 by 32 hitbox to 8 by 8 texture
    _hitbox.setSize(sf::Vector2f(8, 8));
    _hitbox.setPosition(futurePos.left -1, futurePos.top -5);
    _movebox.setSize(sf::Vector2f(futurePos.width, futurePos.height));
    _movebox.setPosition(futurePos.left, futurePos.top);
    _sprite.move(_direction);
}



bool Player::collides(sf::FloatRect element) {
    sf::FloatRect boundings = _sprite.getGlobalBounds();
    if (boundings.intersects(element)) {
        return true;
    }
    return false;
};
