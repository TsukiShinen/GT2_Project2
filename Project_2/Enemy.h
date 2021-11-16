#pragma once
#include <SFML/Graphics.hpp>
#include "ProgressBar.h"
#include "Entity.h"
#include "Utils.h"

class Enemy : public Entity
{
	enum class State { NONE, WALK, FOLLOW, ATTACK, CHANGEDIR, DIE };

	sf::IntRect m_zone;
	float m_range{ 64.f };

	State m_currentState = State::NONE;
	Utils::Direction m_direction;
	float m_chronoChangeDir = 0;
	float m_elapsedTime = 0;
	float m_timeIdle = 2;
	float m_chronoDie = 0;
	float m_timeDie = 0;

	sf::Texture m_textureLifeBar;
	ProgressBar m_lifeBar;

	void Walk(sf::Time& deltaTime, const sf::Vector2f& playerPos);
	void Follow(sf::Time& deltaTime, const sf::Vector2f& playerPos);
	void Attack(sf::Time& deltaTime);
	void ChangeDir(sf::Time& deltaTime, const sf::Vector2f& playerPos);
	void Die(sf::Time& deltaTime);

	void triggerFollow(const sf::Vector2f& playerPos);

	void setAnimations();

	void updateAnimation(sf::Time& deltaTime);
public:
	Enemy(sf::IntRect& zone, const sf::Texture* texture, const sf::Texture* lifebarTexture);

	void update(sf::Time& deltaTime, const sf::Vector2f& playerPos);
	void draw(sf::RenderWindow& window, bool debugMode) override;

	sf::FloatRect getBoundingBox() override;

	void takeDamage(float damage, sf::Time& deltaTime, float cooldown);
	void takeDamage(float damage) override;
};

