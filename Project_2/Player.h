#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Player : public sf::Sprite
{
private:
	float _speed = 60.f;
	sf::Vector2f _direction {0.f, 0.f};
	bool _debug = true;
	//std::vector<sf::IntRect> _anim;
	sf::RectangleShape _hitbox;
	sf::RectangleShape _movebox;
public:
	void update(sf::Time, std::vector<sf::FloatRect>&);
	void draw(sf::RenderWindow&);
	bool collides(sf::FloatRect);
	void changeShowDebug() { _debug = !_debug; }
	
};

