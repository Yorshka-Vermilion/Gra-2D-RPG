#pragma once

#include <SFML\Graphics.hpp>
#include "Przemek/rysowanie.h"
#include "../Silnik2D-SFML/Sebix.h"

class Przemek
{
	sf::RenderWindow* window;
	sf::Image screen;
	sf::Sprite screenCheck;

public:
	Przemek() {
		this->window = new sf::RenderWindow(sf::VideoMode(900, 600), "linie");

	}
	void start() { // Funkcja uruchamiająca program
		while (this->window->isOpen()) {
			window->display();
			window->clear(sf::Color::Black);
			wykonaj(1, 1, 400, 400, this->window); // ukosna od lewej
			wykonaj(450, 450, 30, 30, this->window);
			//wykonaj(280, 30, 10, 300, this->window);
			//wykonaj(40, 70, 640, 480, this->window);
			//wykonaj(20, 20, 30, 300, this->window);
			wykonaj(600, 400, 10, 10, this->window);
		}
	}
};
