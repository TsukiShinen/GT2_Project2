#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Entity.h"
#include "AnimationController.h"
#include "Sword.h"
#include "Utils.h"

class Player : public Entity
{
private:
	std::string m_directionAnim = "WalkBL";
	sf::Vector2f m_direction {0.f, 0.f};

	float m_duration = 1.f;
	float m_time = 0.f;
	bool m_attack = false;
	Sword m_sword;


	sf::RectangleShape m_movebox;
public:
	Player(const sf::Texture* texture);
	void setAnimation();

	void attack() { if (!m_attack) { m_attack = true; } };
	bool isAttacking(sf::Vector2f);
	void update(sf::Time, std::vector<sf::FloatRect>&);
	void draw(sf::RenderWindow&, bool);
	void changeSprite();

	float getDamage() { return m_sword.getDamage(); }
	sf::FloatRect getBoundingBox() override;


};

