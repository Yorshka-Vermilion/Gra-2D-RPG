#pragma once

#include <SFML/Graphics.hpp>

class Point2D {
public:
	int x;
	int y;
	sf::Color color;

	Point2D(int x, int y, sf::Color color) {
		this->x = x;
		this->y = y;
		this->color = color;
	}
};