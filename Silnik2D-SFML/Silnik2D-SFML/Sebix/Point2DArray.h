#pragma once
#include <SFML\Graphics.hpp>
#include "Point2D.h"


class Point2DArray : public sf::VertexArray {
public:
	std::vector<Point2D> p2da;
	Point2DArray() : sf::VertexArray() {}
	Point2DArray(sf::PrimitiveType pt, size_t v) : sf::VertexArray(pt, v) {}
	Point2DArray(std::vector<sf::Vector2f> v2f, sf::Color c) {
		for (int i = 0; i < v2f.size(); i++) {
			p2da.push_back(Point2D(v2f[i], c));
		}
	}

	void add2DPoint(sf::Vector2f v2f){
		p2da.push_back(Point2D(v2f, p2da[0].color));
	}
	
};