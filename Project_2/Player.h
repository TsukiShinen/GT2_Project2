#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Player : public sf::Sprite
{
private:
	float _speed = 100.f;
	sf::Vector2f _direction {0.f, 0.f};
	//std::vector<sf::IntRect> _anim;

public:
	void update(sf::Time, std::vector<sf::RectangleShape>&);
	bool collides(sf::Vector2f);
	
	void animate();
};

