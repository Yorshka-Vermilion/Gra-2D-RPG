#pragma once
#include "Animacja.h"
#include "../Sebix.h"
#include "Gracz.h"
#include "ObslugaRuchuGracza.h"
#include "Mapa.h"
#include "Obiekt.h"


/**
 * @brief Klasa opisujaca MenuGlowne
 * 
 */
class MenuGlowne : public Stan
{
	///Obiekt Demo
	Mapa* map;
	Obiekt* maska;

public:

	/**
	 * @brief Tworzy nowy obiekt MenuGlowne
	 * 
	 * @param window Okno
	 * @param stos Stos stanow
	 * @param event Eventy
	 */
	MenuGlowne(sf::RenderWindow* window, std::stack<Stan*>* stos, sf::Event* event) : Stan(window, stos, event) {
		this->map = new Mapa(25, window->getSize());

		//Maska
		this->maska = new Obiekt("maska.png", sf::Vector2f(0, 0));
		this->maska->setOriginOnMiddle();
		this->maska->przestaw(sf::Vector2f(990, 540));
		this->maska->przeskaluj(sf::Vector2f(1.55,1.15));
	}

	/**
	 * @brief Niszczy MenuGlowne
	 * 
	 */
	~MenuGlowne() {
	
	}

	/**
	 * @brief Rysuje obiekty znajdujace sie w menu glownym
	 * 
	 * @param target Obiekt typu RenderTarget w ktorym beda renderowane obiekty
	 */
	void draw(sf::RenderTarget* target) { /// Rysowanie obiektow na ekranie
		if (!target) target = this->window;
		this->map->draw(target);
		this->maska->rysuj(target);
	};

	/**
	 * @brief Odswieza stan MenuGlowne
	 * 
	 * @param dtime Kontrola czasu
	 */
	void update(const float& dtime) { /// Odswiezenie stanu aktualnego "stanu"
		this->dtime = dtime;
		if (!this->prawy && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			this->map->Przesun(2);
		}
		else if (!this->lewy && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->map->Przesun(3);
		}

		sprawdzMysz();
		
	};
};

