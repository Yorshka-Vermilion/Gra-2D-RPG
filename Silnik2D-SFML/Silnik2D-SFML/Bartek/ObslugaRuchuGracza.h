#pragma once
#include "Gracz.h"
class ObslugaRuchuGracza
{
	Gracz *gracz; // Wskaznik na obiekt gracza
	float szybkosc; // Predkosc ruchu
public:
	ObslugaRuchuGracza(Gracz* gracz, float szybkosc) {
		this->gracz = gracz;
		this->szybkosc = szybkosc;
	}

	
	void update(const float& Zegar) { /// Odswiezenie stanu ruchu
		float x = this->gracz->pobierzPozycje().x;
		float y = this->gracz->pobierzPozycje().y;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			this->gracz->rusz(sf::Vector2f(x, y - (szybkosc*Zegar)));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			this->gracz->rusz(sf::Vector2f(x, y + (szybkosc * Zegar)));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			this->gracz->rusz(sf::Vector2f(x + (szybkosc * Zegar), y));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			this->gracz->rusz(sf::Vector2f(x - (szybkosc * Zegar), y));
		}
	}
};

