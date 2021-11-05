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
	

public:
	Animation(float duration, std::vector<sf::IntRect> list) :
		m_list(list) {};
	void play() { m_playing = true; };
	void stop();
	sf::IntRect getRect() { return m_list[m_currentIndex]; }
	void update(sf::Time deltaTime);
	void resetIndex(int index) { m_currentIndex = 0; }
};

