#pragma once
#include <SFML/Graphics.hpp>
#include "Point.h"
#include "ProgressBar.h"
#include "AnimationController.h"

class Enemy
{
	struct Direction {
		bool up = false;
		bool right = true;
		bool down = true;
		bool left = false;

		void reset() {
			up = false;
			right = false;
			down = false;
			left = false;
		}
	};

	const enum class State { NONE, WALK, FOLLOW, ATTACK, CHANGEDIR };

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::IntRect* m_zone;
	sf::Vector2f m_velocity{ 0.f, 0.f };
	float m_speed{ 20.f };
	float m_range{ 30.f };
	Direction m_direction;

	State m_currentState = State::NONE;

	sf::Texture m_textureLifeBar;
	ProgressBar m_lifeBar;

	float m_chronoChangeDir = 0;
	float m_timeIdle = 2;

	AnimationController m_animationController;

	void Walk(sf::Time& deltaTime, sf::Vector2f playerPos);
	void Follow(sf::Time& deltaTime, sf::Vector2f playerPos);
	void Attack(sf::Time& deltaTime);
	void ChangeDir(sf::Time& deltaTime);
public:
	Enemy(sf::IntRect* zone);

	void update(sf::Time& deltaTime, sf::Vector2f playerPos);
	void draw(sf::RenderWindow& window);
};

