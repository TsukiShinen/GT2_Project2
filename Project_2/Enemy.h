#pragma once
#include <SFML/Graphics.hpp>
#include "ProgressBar.h"
#include "Entity.h"

class Enemy : public Entity
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

	sf::IntRect* m_zone;
	float m_range{ 30.f };
	Direction m_direction;

	State m_currentState = State::NONE;

	sf::Texture m_textureLifeBar;
	ProgressBar m_lifeBar;

	float m_chronoChangeDir = 0;
	float m_timeIdle = 2;

	void Walk(sf::Time& deltaTime, sf::Vector2f playerPos);
	void Follow(sf::Time& deltaTime, sf::Vector2f playerPos);
	void Attack(sf::Time& deltaTime);
	void ChangeDir(sf::Time& deltaTime);

	void setAnimations();
public:
	Enemy(sf::IntRect* zone);

	void update(sf::Time& deltaTime, sf::Vector2f playerPos);
	void draw(sf::RenderWindow& window, bool debugMode);

	sf::FloatRect getBoundingBox() override;
};

