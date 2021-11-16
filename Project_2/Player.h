#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <functional>
#include "Entity.h"
#include "AnimationController.h"
#include "Inventaire.h"
#include "Sword.h"
#include "Utils.h"
#include "ProgressBar.h"

class Player : public Entity
{
public:
	Player(const sf::Texture* texture, const sf::Texture* inventoryTexture, const sf::Texture* itemSelectedTexture);
	void setAnimation();

	void attack();
	bool isAttacking(sf::Vector2f);

	sf::FloatRect intersects(std::vector<sf::FloatRect>& listOfElements);
	void update(sf::Time, std::vector<sf::FloatRect>&);

	void draw(sf::RenderWindow&, bool);
	void drawUI(sf::RenderWindow&, bool);

	void changeSprite();

	float getDamage() { return m_sword.getDamage(); }
	sf::FloatRect getBoundingBox() override;
	void takeDamage(float damage) override;

	bool pickItem(Item* item);

	std::function<void(int)> heal;

	double calcAngle();

	void setProgressBar(ProgressBar& progressBar);

	void keypressed(sf::Keyboard::Key keyCode);
private:
	std::string m_directionAnim = "WalkBL";
	Utils::Direction m_direction;

	ProgressBar m_lifeBar;

	sf::RectangleShape m_movebox;
	Inventaire m_inventaire;

	const sf::FloatRect m_walkingBox = sf::FloatRect(1, 6, 6, 2);

	int angle = 0;
	bool m_isInventoryOpen = false;
	float m_duration = 1.f;
	float m_time = 0.f;
	bool m_attack = false;
	Sword m_sword;
};

