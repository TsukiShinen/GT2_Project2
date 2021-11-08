#include "AnimationController.h"
#include "Point.h"

void AnimationController::changeCurrentAnim(std::string name) {
	m_animations[m_animationName].stop();
	m_animationName = name;
	m_animations[m_animationName].play();
}

void AnimationController::update(sf::Time deltaTime) {
	m_animations[m_animationName].update(deltaTime);
}

std::vector<sf::IntRect> AnimationController::getAllRect(std::vector<int> lstId) 
{
	std::vector<sf::IntRect> lstRect;

	for (int& id : lstId) {
		Point pos(id % m_columns, id / m_columns);

		lstRect.push_back(sf::IntRect(pos.x * m_tileSizeX, pos.y * m_tileSizeY, m_tileSizeX, m_tileSizeY));
	}

	return lstRect;

	//int x = columnNumber * size;
	//int y = lineNumber * size;
	//std::vector < sf::IntRect > vectorList;
	//for (int e = 0; e < numberOfLineOfSprite; e++) {
	//	for (int i = 0; i < numberOfCollumnOfSprite; i++) {
	//		vectorList.push_back(sf::IntRect(x + (i * size), y + (e * size), size, size));
	//	}
	//}
	//return vectorList;
}