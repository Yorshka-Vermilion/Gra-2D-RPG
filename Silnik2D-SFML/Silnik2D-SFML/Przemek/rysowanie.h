#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Sebix.h"


void linia_powyzej45(int x0, int y0, int x1, int y1, sf::RenderWindow* window) {
	int x;
	float dy, dx, y, m;
	Sebix* s = new Sebix(window);

	if (x0 > x1) {
		dy = y0 - y1;
		dx = x0 - x1;

		m = dy / dx;

		if (dx == 0) {
			y = 0;
			for (x = x1; x <= x0; x++) {
				Point2D* p = new Point2D(x, (int)(y), sf::Color::Blue);
				s->draw2DPoint(p);
				delete(p);
			}
		}
		else {
			y = y1;
			for (x = x1; x <= x0; x++) {
				Point2D* p = new Point2D(x, (int)(y + 0.5), sf::Color::Blue);
				y += m;
				s->draw2DPoint(p);
				delete(p);
			}
		}
	}

	else {
		dy = y1 - y0;
		dx = x1 - x0;


		m = dy / dx;
		if (dx == 0) {
			y = 0;
			for (x = x0; x <= x1; x++) {
				Point2D* p = new Point2D(x, (int)(y), sf::Color::Blue);
				s->draw2DPoint(p);
				delete(p);
			}
		}
		else {
			y = y0;
			for (x = x0; x <= x1; x++) {
				Point2D* p = new Point2D(x, (int)(y + 0.5), sf::Color::Blue);
				y += m;
				s->draw2DPoint(p);
				delete(p);
			}
		}
	}
}


void linia_ponizej45(int x0, int y0, int x1, int y1, sf::RenderWindow* window) {
	int y;
	float dy, dx, m, x;

	Sebix* s = new Sebix(window);

	if (x0 > x1) {
		dy = y1 - y0;
		dx = x1 - x0;

		m = dx / dy;

		if (dy == 0) {
			x = 0;
			for (y = y1; y <= y0; y++) {
				Point2D* p = new Point2D((int)(x), y, sf::Color::Blue);
				s->draw2DPoint(p);
				delete(p);
			}
		}
		else {
			x = x1;
			for (y = y1; y <= y0; y++) {
				Point2D* p = new Point2D((int)(x + 0.5), y, sf::Color::Blue);
				x += m;
				s->draw2DPoint(p);
				delete(p);
			}
		}
	}

	else {
		dy = y0 - y1;
		dx = x0 - x1;

		m = dx / dy;
		if (dy == 0) {
			x = 0;
			for (y = y0; y <= y1; y++) {
				Point2D* p = new Point2D((int)(x), y, sf::Color::Blue);
				s->draw2DPoint(p);
				delete(p);
			}
		}
		else {
			x = x0;
			for (y = y0; y <= y1; y++) {
				Point2D* p = new Point2D((int)(x + 0.5), y, sf::Color::Blue);
				x += m;
				s->draw2DPoint(p);
				delete(p);
			}
		}
	}
}

void wykonaj(int x0, int y0, int x1, int y1, sf::RenderWindow* window) {

	float dy, dx, m;

	dy = y1 - y0;
	dx = x1 - x0;

	m = dy / dx;

	if (m <= 1 && m >= -1) {
		linia_powyzej45(x0, y0, x1, y1, window);

	}
	if (m > 1 || m < -1) {
		linia_ponizej45(x0, y0, x1, y1, window);
	}
}