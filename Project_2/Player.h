#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Entity.h"
#include "AnimationController.h"

class Player : public Entity
{
private:
	std::string m_directionAnim = "WalkBL";
	sf::Vector2f m_direction {0.f, 0.f};

	sf::RectangleShape m_movebox;
public:
	Player(const sf::Texture* texture);
	void setAnimation();

	void update(sf::Time, std::vector<sf::FloatRect>&);
	void draw(sf::RenderWindow&, bool);

	void changeSprite();

	sf::FloatRect getBoundingBox() override;
};

