#pragma once
#include "Gracz.h"
#include "../Sebix/DrzewoDialogow.h"

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
	
	DrzewoDialogow* drzewo;

public:
	/**
	 * @brief Tworzy nowy obiekt obslugi ruchu gracza
	 * 
	 * @param gracz Wskaznik na obiekt typu Gracz
	 * @param szybkosc Szybkosc ruchu
	 */
	ObslugaRuchuGracza(Gracz* gracz, float szybkosc, DrzewoDialogow *drzewo) {
		this->gracz = gracz;
		this->szybkosc = szybkosc;
		this->drzewo = drzewo;
	}
	~ObslugaRuchuGracza() {
		delete(this->gracz);
	}

	/**
	 * @brief Odswieza stan obiektu ObslugaRuchuGracza
	 * 
	 * @param Zegar Kontrola czasu
	 */
	void update(const float& Zegar) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
				this->gracz->rusz(sf::Vector2f(this->gracz->pobierzPozycje().x, this->gracz->pobierzPozycje().y - (szybkosc * Zegar)));
				//std::cout << "gora" << std::endl;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
				this->gracz->rusz(sf::Vector2f(this->gracz->pobierzPozycje().x, this->gracz->pobierzPozycje().y + (szybkosc * Zegar)));
				//std::cout << "dol" << std::endl;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
				this->gracz->rusz(sf::Vector2f(this->gracz->pobierzPozycje().x + (szybkosc * Zegar), this->gracz->pobierzPozycje().y));
				//std::cout << "prawo" << std::endl;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
				this->gracz->rusz(sf::Vector2f(this->gracz->pobierzPozycje().x - (szybkosc * Zegar), this->gracz->pobierzPozycje().y));
				//std::cout << "lewo" << std::endl;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
				this->gracz->zadajObrazenia();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::H)) {
				this->gracz->uleczObrazenia();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::M)) {
				this->gracz->odejmijMane();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::N)) {
				this->gracz->ladujMane();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
				this->gracz->dodajExp(10);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) {
				this->drzewo->stworzDialog();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P)) {
				this->drzewo->przeprowadzDialog();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) {
				this->drzewo->dodajDialog();
			}
	}
};



