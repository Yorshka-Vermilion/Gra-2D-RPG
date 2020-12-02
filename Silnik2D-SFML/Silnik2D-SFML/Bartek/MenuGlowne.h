#pragma once
#include "Animacja.h"
#include "../Sebix.h"
#include "Gracz.h"
#include "ObslugaRuchuGracza.h"

/**
 * @brief Klasa opisujaca MenuGlowne
 * 
 */
class MenuGlowne : public Stan
{
	///Obiekt Demo


public:

	/**
	 * @brief Tworzy nowy obiekt MenuGlowne
	 * 
	 * @param window Okno
	 * @param stos Stos stanow
	 * @param event Eventy
	 */
	MenuGlowne(sf::RenderWindow* window, std::stack<Stan*>* stos, sf::Event* event) : Stan(window, stos, event) {
	
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
	
	};

	/**
	 * @brief Odswieza stan MenuGlowne
	 * 
	 * @param dtime Kontrola czasu
	 */
	void update(const float& dtime) { /// Odswiezenie stanu aktualnego "stanu"
		this->dtime = dtime;
		sprawdzMysz();

	};
};

