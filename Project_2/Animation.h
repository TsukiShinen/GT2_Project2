#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Animation
{
	bool m_playing = false;
	std::vector<sf::IntRect> m_list;
	int m_currentIndex = 0;
	float m_time = 0;
	float m_duration = 0;
	std::string m_nextAnim = "";
public:
	Animation(std::vector<sf::IntRect> list = std::vector<sf::IntRect>(), float duration = 0.f) :
		m_list(list), m_duration(duration) {};
	//Animation(std::vector<sf::IntRect> list = std::vector<sf::IntRect>(), float duration = 0.f, std::string nextAnim = "") : // LAAAAAAAAAAA
	//	m_list(list), m_duration(duration) {};
	void play() { m_playing = true; };
	void stop();
	sf::IntRect getRect() { return m_list[m_currentIndex]; }
	void update(sf::Time deltaTime);
	// bool update(sf::Time deltaTime);
	void resetIndex(int index) { m_currentIndex = 0; }
	size_t getEndIndex() { return m_list.size() - m_currentIndex - 1; }
};

