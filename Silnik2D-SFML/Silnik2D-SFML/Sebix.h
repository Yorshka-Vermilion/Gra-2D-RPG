#pragma once
#include "Point2D.h"
#include <SFML\Graphics.hpp>

class Sebix{
	sf::RenderWindow *window; // Okno programu przekazane z klasy Engine
	Point2D *pixel; // Ustawienia pixela

	sf::RectangleShape draw2DPoint(Point2D *p2d) { // Funkcja odpowiada za rysowanie pixeli na ekranie
		sf::RectangleShape pixel;
		pixel.setFillColor(p2d->color);
		pixel.setPosition(p2d->x, p2d->y);
		pixel.setSize({1,1});
		this->window->draw(pixel);
		return pixel;
	}

	template <typename T> // Funkcja odpowiada za działanie klawiatury
	void keyboard(sf::Keyboard::Key k, T function) {
		if (sf::Keyboard::isKeyPressed(k)) {
			function;
		}
	}

	template <typename T>
	void mouse(sf::Mouse::Button b, T function) {
		if (sf::Mouse::isButtonPressed(b)) {
			function;
		}
	}

public:
	Sebix(sf::RenderWindow *window) {
		this->window = window;
		this->pixel = new Point2D(0, 0, sf::Color::Magenta);
	}

	void run() {
		if(this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)).x > this->window->getSize().x || this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)).x < 0)
			this->pixel->x = 0;
		else {
			this->pixel->x = sf::Mouse::getPosition().x;
		}
		
		if (this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)).y > this->window->getSize().y || this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window)).y < 0)
			this->pixel->y = 0;
		else {
			this->pixel->y = sf::Mouse::getPosition().y;
		}
		this->pixel->color = sf::Color::Magenta;
		keyboard(sf::Keyboard::Left, draw2DPoint(pixel));
		
	}
};

