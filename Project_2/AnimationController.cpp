#include "AnimationController.h"

void AnimationController::changeCurrentAnim(std::string name) {
	m_animations[m_animationName].stop();
	m_animationName = name;
	m_animations[m_animationName].play();
}


void AnimationController::update(sf::Time deltaTime) {
	m_animations[m_animationName].update(deltaTime);
}