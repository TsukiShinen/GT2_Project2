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

class Player : public Entity
{
public:
	Player(const sf::Texture* texture, const sf::Texture* inventoryTexture, const sf::Texture* itemSelectedTexture);
	void setAnimation();

	void attack();
	bool isAttacking(sf::Vector2f);
	void update(sf::Time, std::vector<sf::FloatRect>&);
	void draw(sf::RenderWindow&, bool);
	void drawUI(sf::RenderWindow&, bool);

	void changeSprite();

	float getDamage() { return m_sword.getDamage(); }
	sf::FloatRect getBoundingBox() override;

	bool pickItem(Item* item);

	std::function<void(int)> heal;

	void keypressed(sf::Keyboard::Key keyCode);
private:
	std::string m_directionAnim = "WalkBL";
	sf::Vector2f m_direction{ 0.f, 0.f };

	sf::RectangleShape m_movebox;
	Inventaire m_inventaire;

	int angle = 0;
	bool m_isInventoryOpen = false;
	float m_duration = 1.f;
	float m_time = 0.f;
	bool m_attack = false;
	Sword m_sword;
};

