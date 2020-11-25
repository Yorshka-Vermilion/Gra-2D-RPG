#pragma once
#include "Gracz.h"

/**
 * @brief Klasa sluzaca do obslugi ruchu gracza
 * 
 */
class ObslugaRuchuGracza
{
	/// Wskaznik na obiekt gracza
	Gracz *gracz; 
	/// Predkosc ruchu
	float szybkosc;
public:
	/**
	 * @brief Tworzy nowy obiekt obslugi ruchu gracza
	 * 
	 * @param gracz Wskaznik na obiekt typu Gracz
	 * @param szybkosc Szybkosc ruchu
	 */
	ObslugaRuchuGracza(Gracz* gracz, float szybkosc) {
		this->gracz = gracz;
		this->szybkosc = szybkosc;
	}

	/**
	 * @brief Odswieza stan obiektu ObslugaRuchuGracza
	 * 
	 * @param Zegar Kontrola czasu
	 */
	void update(const float& Zegar) {
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

