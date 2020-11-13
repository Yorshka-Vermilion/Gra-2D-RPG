#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Point2DArray.h"
#include "Point2D.h"
#include "LineSegment.h"

void draw2DPoint(Point2D p2d, sf::RenderTarget* target = nullptr) { // Funkcja odpowiada za rysowanie pixeli na ekranie
	target->draw(&p2d, 1, sf::PrimitiveType::Points);
}

void draw2DPoints(Point2DArray p2da, sf::RenderTarget* target = nullptr) { // Funkcja odpowiada za rysowanie zbioru punktów na ekranie
	target->draw(&p2da.p2da[0], p2da.p2da.size(), sf::PrimitiveType::Points);
}

void draw2DLine(Point2DArray p2da, sf::RenderTarget* target = nullptr) { // Funkcja odpowiada za rysowanie lini na ekranie
	target->draw(&p2da.p2da[0], p2da.p2da.size(), sf::PrimitiveType::Lines);
}

void draw2DTriangle(Point2DArray p2da, sf::RenderTarget* target = nullptr) { // Funkcja odpowiada za trójk¹tów na ekranie
	target->draw(&p2da.p2da[0], p2da.p2da.size(), sf::PrimitiveType::Triangles);
}

void draw2DQuad(Point2DArray p2da, sf::RenderTarget* target = nullptr) { // Funkcja odpowiada za rysowanie kwadratów na ekranie
	target->draw(&p2da.p2da[0], p2da.p2da.size(), sf::PrimitiveType::Quads);
}


void draw2DEmpty(Point2DArray p2da, sf::RenderTarget* target = nullptr) {
	if (p2da.p2da.size() > 0) {
		if (p2da.p2da.size() == 1)
			draw2DPoints(p2da, target);
		else if (p2da.p2da.size() == 2)
			draw2DLine(p2da, target);
		else {
			target->draw(&p2da.p2da[0], p2da.p2da.size(), sf::PrimitiveType::LineStrip);
			Point2D line[] = {
				Point2D(p2da.p2da[0].position, p2da.p2da[0].color),
				Point2D(p2da.p2da[p2da.p2da.size() - 1].position, p2da.p2da[p2da.p2da.size() - 1].color)
			};
			target->draw(line, 2, sf::PrimitiveType::Lines);
		}
	}
}

void drawLinePrzyrostowo(LineSegment ls, sf::RenderTarget* target = nullptr) {
	float dy, dx, y, m;
	sf::Vector2f v2fs = ls.getStartVector();
	sf::Vector2f v2fe = ls.getEndVector();
	dy = abs(v2fe.y - v2fs.y);
	dx = abs(v2fe.x - v2fs.x);

	if (v2fs.y < v2fe.y) y = v2fs.y;
	else y = v2fe.y;

	if (dx != 0) {
		if (dy / dx <= -1 || dy / dx >= 1) std::swap(dx, dy);
		m = dy / dx;
	}
	else m = 0;

	if (dx != 0) {
		if (v2fs.x <= v2fe.x) {
			for (int i = (int)v2fs.x; i <= (int)v2fe.x; i++) {
				draw2DPoint(Point2D(sf::Vector2f(i, (int)(y + 0.5)), ls.getStart().color), target);
				y += m;
			}
		}
		else {
			for (int i = (int)v2fe.x; i <= (int)v2fs.x; i++) {
				draw2DPoint(Point2D(sf::Vector2f(i, (int)(y + 0.5)), ls.getStart().color), target);
				y += m;
			}
		}
	}
	else {
		if (v2fs.y <= v2fe.y) {
			for (int i = (int)v2fs.y; i <= (int)v2fe.y; i++) {
				draw2DPoint(Point2D(sf::Vector2f(v2fs.x, i), ls.getStart().color), target);
			}
		}
		else {
			for (int i = (int)v2fe.y; i <= (int)v2fs.y; i++) {
				draw2DPoint(Point2D(sf::Vector2f(v2fs.x, i), ls.getStart().color), target);
				y += m;
			}
		}
	}
}

