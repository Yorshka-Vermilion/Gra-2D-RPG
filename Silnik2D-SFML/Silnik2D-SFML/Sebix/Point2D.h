#pragma once

#include <SFML/Graphics.hpp>

class Point2D : public sf::Vertex {
public:

	Point2D(const sf::Vector2f& xy, const sf::Color& color) : sf::Vertex(xy,color){}
	Point2D() {}

	float getX() {
		return this->position.x;
	}

	float getY() {
		return this->position.y;
	}
};


