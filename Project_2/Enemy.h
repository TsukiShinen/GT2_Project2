#pragma once
#include <SFML/Graphics.hpp>
#include "Point.h"
#include "ProgressBar.h"

class Enemy
{
	const enum class State { NONE, WALK, FOLLOW, ATTACK, CHANGEDIR };

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::IntRect* m_zone;
	sf::Vector2f m_velocity{ 0.f, 0.f };
	float m_speed{ 20.f };

	State m_currentState = State::NONE;

	sf::Texture m_textureLifeBar;
	ProgressBar m_lifeBar;

	float m_chronoChangeDir = 0;
	float m_timeIdle = 2;

	void Walk(sf::Time& deltaTime);
	void Follow(sf::Time& deltaTime);
	void Attack(sf::Time& deltaTime);
	void ChangeDir(sf::Time& deltaTime);
public:
	Enemy(sf::IntRect* zone);

	void update(sf::Time& deltaTime);
	void draw(sf::RenderWindow& window);
};

