#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "AnimationController.h"

class Entity
{
public:
	Entity(std::string name, size_t life, const sf::Texture* texture);

	virtual void update(sf::Time& deltaTime);
	virtual void draw(sf::RenderWindow& window, bool debugMode);

	virtual sf::FloatRect getBoundingBox() { return m_sprite.getGlobalBounds(); }
	void setPosition(sf::Vector2f position);
	const sf::Vector2f& getSize();
	const sf::Vector2f& getPosition();
	const sf::Vector2f& getCenter();
	int getMapLevel();
	void setMapLevel(int level);

	virtual bool collides(const sf::FloatRect& rect);
	virtual void takeDamage(float damage);

	bool toRemove();
	bool isAlive();
protected:
	std::string m_name{ "Entity" };
	float m_life{ 0 };

	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_size;
	AnimationController m_animationController;

	float m_speed{ 0.f };
	float m_friction{ 0.1f };
	float m_masse{ 45.f };
	sf::Vector2f m_velocity{ 0.f, 0.f };

	int m_mapLevel = 0;

	bool m_toRemove = false;
private:
	sf::Vector2f m_vitessse{ 0, 0 };
};
