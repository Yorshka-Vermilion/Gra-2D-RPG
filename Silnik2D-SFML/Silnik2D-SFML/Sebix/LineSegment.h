#pragma once
#include <SFML\Graphics.hpp>
#include "Point2D.h"


class LineSegment {
	Point2D start;
	Point2D end;
public:
	LineSegment(Point2D s = Point2D(sf::Vector2f(0.f, 0.f), sf::Color::Magenta), Point2D e = Point2D(sf::Vector2f(100.f, 100.f), sf::Color::Magenta)) : start(s), end(e) {}
	LineSegment(std::vector<sf::Vector2f> v2f, sf::Color c){
		start = Point2D(v2f[0], c);
		end = Point2D(v2f[1], c);
	}

	Point2D getStart() {
		return this->start;
	}

	Point2D getEnd() {
		return this->start;
	}

	sf::Vector2f getStartVector() {
		return sf::Vector2f(this->start.position);
	}

	sf::Vector2f getEndVector() {
		return sf::Vector2f(this->end.position);
	}

	void setStart(sf::Vector2f start) {
		this->start.position = start;
	}

	void setStart(float x, float y) {
		this->start.position = sf::Vector2f(x,y);
	}

	void setEnd(sf::Vector2f end) {
		this->end.position = end;
	}

	void setEnd(float x, float y) {
		this->end.position = sf::Vector2f(x, y);
	}
};