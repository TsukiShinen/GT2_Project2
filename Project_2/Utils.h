#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

#include "json.h"
using json = nlohmann::json;

class Utils
{
public:
	struct Direction {
		bool up = false;
		bool right = true;
		bool down = true;
		bool left = false;

		void reset() {
			up = false;
			right = false;
			down = false;
			left = false;
		}
	};

	static json readJson(std::string fileName) {
		json jsonParesed;

		std::ifstream reader(fileName);
		reader >> jsonParesed;
		reader.close();
		
		return jsonParesed;
	}

	static double angle(const sf::Vector2f& point1, const sf::Vector2f& point2) {
		return atan2(point2.y - point1.y, point2.x - point1.x);
	}

	static double dist(const sf::Vector2f& point1, const sf::Vector2f& point2) {
		return pow(((point2.x - point1.x) * (point2.x - point1.x) + (point2.y - point1.y) * (point2.y - point1.y)), 0.5f);
	}

	static float norme(const sf::Vector2f& vector) {
		return sqrt(vector.x * vector.x + vector.y * vector.y);
	}

	static sf::Vector2f normalize(const sf::Vector2f& vector) {
		float n = norme(vector);
		if (n != 0) {
			return vector / n;
		}
		return sf::Vector2f(0, 0);
	}

	static float shortestAngle(float angle1, float angle2) {
		return fmod(angle2 - angle1 + 180, 360) - 180;
	}
	static int shortestAngle(int angle1, int angle2) {
		return (angle2 - angle1 + 180) % 360 - 180;
	}

	static int modAngle(int angle) {
		return (angle + 360) % 360;
	}
	static float modAngle(float angle) {
		return fmod(angle + 360, 360);
	}
};

