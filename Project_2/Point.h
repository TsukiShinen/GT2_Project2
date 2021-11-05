#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

struct Point
{
	int x;
	int y;

	Point(int pX = 0, int pY = 0) : x(pX), y(pY) {}

	sf::Vector2f toVector2() { return sf::Vector2f(x, y); }

	friend std::ostream& operator<<(std::ostream& os, const Point& point) {
		os << point.x << ", " << point.y;
		return os;
	}

	Point operator/(int division) {
		return Point(this->x / division, this->y / division);
	}
};

