#include "Animation.h"

//void Animation::update(sf::Time deltaTime) {
//	if (!m_playing) { return; }
//	m_time += deltaTime.asSeconds();
//	if (m_time>m_duration) {
//		m_time = 0;
//		m_currentIndex++;
//		if (m_currentIndex >= m_list.size()) {
//			m_currentIndex = 0;
//		}
//	}
//}

bool Animation::update(sf::Time deltaTime) {
	if (!m_playing) { return; }
	m_time += deltaTime.asSeconds();
	if (m_time > m_duration) {
		m_time = 0;
		m_currentIndex++;
		if (m_currentIndex >= m_list.size()) {
			return true;
		}
	}
	return false;
}
void Animation::stop() { 
	m_playing = false;
	m_currentIndex = 0;
}