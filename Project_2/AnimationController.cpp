#include "AnimationController.h"

void AnimationController::changeCurrentAnim(std::string name) {
	m_animations[m_animationName].stop();
	m_animationName = name;
	m_animations[m_animationName].play();
}

void AnimationController::update(sf::Time deltaTime) {
	m_animations[m_animationName].update(deltaTime);
}

std::vector < sf::IntRect > AnimationController::getAllRect(int lineNumber, int columnNumber, int size, int numberOfCollumnOfSprite, int numberOfLineOfSprite) {
	int x = columnNumber * size;
	int y = lineNumber * size;
	std::vector < sf::IntRect > vectorList;
	for (int e = 0; e < numberOfLineOfSprite; e++) {
		for (int i = 0; i < numberOfCollumnOfSprite; i++) {
			vectorList.push_back(sf::IntRect(x + (i * size), y + (e * size), size, size));
		}
	}
	return vectorList;
}