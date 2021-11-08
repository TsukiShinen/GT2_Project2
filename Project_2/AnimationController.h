#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"

class AnimationController
{
	std::map < std::string, Animation > m_animations;
	std::string m_animationName;

public:
	void setCurrentAnim(std::string anim) { m_animationName; }
	void update(sf::Time deltaTime);
	void changeCurrentAnim(std::string name);
	sf::IntRect getCurrentRect() { return m_animations[m_animationName].getRect(); }
	void adAnimation(std::string name, Animation anim) { m_animations[name] = anim; }
	std::vector < sf::IntRect > getAllRect(int lineNumber, int columnNumber, int size, int numberOfspritesInCollumn, int numberOfSpritesInLine);
};

