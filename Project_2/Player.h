#pragma once
#include <SFML/Graphics.hpp>

class Player : public sf::Sprite
{
private:
	float _speed = 100.f;
	std::pair<float, float> _direction {0.f, 0.f};
	
public:
	void update(sf::Time, std::vector<sf::RectangleShape>&);
	bool collides(sf::Vector2f);
	
};

