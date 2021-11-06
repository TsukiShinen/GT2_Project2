#pragma once
#include <SFML/Graphics.hpp>
#include "Point.h"

class Enemy : public sf::Sprite
{
	const enum class State { NONE, WALK, FOLLOW, ATTACK, CHANGEDIR };

	sf::Texture m_texture;

	sf::IntRect* m_zone;
	sf::Vector2f m_velocity{ 0.f, 0.f };
	float m_speed{ 20.f };

	State m_currentState = State::NONE;

	void Walk(sf::Time deltaTime);
	void Follow();
	void Attack();
	void ChangeDir();

public:
	Enemy(sf::IntRect* zone);

	void update(sf::Time deltaTime);
};

