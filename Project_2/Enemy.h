#pragma once
#include <SFML/Graphics.hpp>

class Enemy : public sf::Sprite
{
	sf::Texture m_texture;

	sf::Vector2f m_velocity{ 0.f, 0.f };
	float m_speed{ 10.f };
	double m_angle{0};

public:
	Enemy();

	void update(sf::Time deltaTime);

	void randomAngle();
};

