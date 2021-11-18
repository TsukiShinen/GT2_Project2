#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <functional>
#include "Entity.h"
#include "AnimationController.h"
#include "Inventory.h"
#include "Sword.h"
#include "Utils.h"
#include "ProgressBar.h"

class Player : public Entity
{
public:
	Player(const sf::Texture* texture, const sf::Texture* inventoryTexture, const sf::Texture* itemSelectedTexture);
	
	void setAnimation();

	void update(sf::Time, std::vector<sf::FloatRect>&);
	void draw(sf::RenderWindow&, bool);
	void drawUI(sf::RenderWindow&, bool);

	void changeSprite();

	float getAttackSpeed() { return m_sword.getAttackSpeed(); }
	float getDamage() { return m_sword.getDamage(); }
	void attack();
	bool isAttacking(sf::Vector2f);
	void takeDamage(float damage) override;
	
	std::function<void(int)> heal;
	bool pickItem(Item* item);
	void setProgressBar(ProgressBar& progressBar);

	sf::FloatRect getBoundingBox() override;

	void keypressed(sf::Keyboard::Key keyCode);
	void movementsOnKeyPressed();
	sf::FloatRect intersects(std::vector<sf::FloatRect>& listOfElements, sf::Time& deltaTime);
	void handleMovement(sf::Time deltaTime, std::vector<sf::FloatRect>& listOfElements);
	
	void updateMoveHistory();
	double calcDirectionAngle();
	void directionChange();
	
	void movementShift();
	bool isInSwitchingMode();

	
private:
	std::string m_directionAnim = "WalkBL";
	Utils::Direction m_direction;

	ProgressBar m_lifeBar;

	sf::RectangleShape m_movebox;
	Inventory m_inventory;

	const sf::FloatRect m_walkingBox = sf::FloatRect(1, 6, 6, 2);
	const sf::FloatRect m_horseHitBox = sf::FloatRect(-6, -5, 13, 12);

	bool m_riding = false;

	bool m_isInventoryOpen = false;

	float m_otherSpeed = 1000.f;
	float m_otherMass = 200.f;
	float m_switchModeDuration = 1.f;
	float m_switchModeTime = 0.f;
	float m_rotationSpeed = 100.f;

	bool m_attack = false;
	Sword m_sword;

	sf::Vector2f m_moveHistory = { 1, 1 };
	sf::Vector2f m_movement = { 0, 0 };

	float chronoAniamtionDie;
	float timeAnimationDie;
};

