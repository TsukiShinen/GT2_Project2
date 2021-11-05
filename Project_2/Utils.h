#pragma once
#include <SFML/Graphics.hpp>
#include "Point.h"

class Utils
{
public:
	static double angle(const Point& point1, const Point& point2) {
		return atan2(point2.y - point1.y, point2.x - point1.x);
	}
	static double angle(const sf::Vector2f& point1, const sf::Vector2f& point2) {
		return atan2(point2.y - point1.y, point2.x - point1.x);
	}

	static double dist(const Point& point1, const Point& point2) {
		return pow((pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2)), 0.5f);
	}
	static double dist(const sf::Vector2f& point1, const sf::Vector2f& point2) {
		return pow((pow(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2)), 0.5f);
	}
};

