#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "AnimationController.h"

class Player 
{
private:
	float _speed = 30.f;
	sf::Vector2f _direction {0.f, 0.f};
	bool _debug = false;
	//std::vector<sf::IntRect> _anim;
	sf::Texture _texture;
	AnimationController _animCtrl;
	sf::Sprite _sprite;
	sf::RectangleShape _hitbox;
	sf::RectangleShape _movebox;
public:
	Player();
	void update(sf::Time, std::vector<sf::FloatRect>&);
	void draw(sf::RenderWindow&);
	bool collides(sf::FloatRect);
	void changeShowDebug() { _debug = !_debug; }
	void setPosition(sf::Vector2f position) { _sprite.setPosition(position); }
	sf::Vector2f getPosition() { return _sprite.getPosition(); }
	void changeSprite();
};

