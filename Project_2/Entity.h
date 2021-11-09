#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "AnimationController.h"

class Entity
{
protected:
	std::string m_name{ "Entity" };
	size_t m_life{ 0 };

	sf::Texture m_texture;
	sf::Sprite m_sprite;
	AnimationController m_animationController;

	float m_speed{ 0.f };
	sf::Vector2f m_velocity{ 0.f, 0.f };
public:
	Entity(std::string name, size_t life, std::string imagePath) :
		m_name(name),
		m_life(life),
		m_sprite(m_texture)
	{
		// Load textures
		if (!m_texture.loadFromFile(imagePath)) {
			std::cout << "Entity : " << m_name << ", can't load image : " << imagePath << std::endl;
		}
	}

	virtual void update(sf::Time& deltaTime);
	virtual void draw(sf::RenderWindow& window, bool debugMode);

	virtual sf::FloatRect getBoundingBox() { return m_sprite.getGlobalBounds(); }
	sf::Vector2f getPosition();
};

