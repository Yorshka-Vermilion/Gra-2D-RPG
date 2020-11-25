#pragma once
#include "Animacja.h"
#include "../Sebix.h"
#include "Gracz.h"
#include "ObslugaRuchuGracza.h"
#include "Demo.h"

/**
 * @brief Klasa opisujaca MenuGlowne
 * 
 */
class MenuGlowne : public Stan
{
	///Obiekt Demo
	Demo* demo;

public:

	/**
	 * @brief Tworzy nowy obiekt MenuGlowne
	 * 
	 * @param window Okno
	 * @param stos Stos stanow
	 * @param event Eventy
	 */
	MenuGlowne(sf::RenderWindow* window, std::stack<Stan*>* stos, sf::Event* event) : Stan(window, stos, event) {
		this->demo = new Demo(window, stos, event);
		demo->demoWczytaj();
	}

	/**
	 * @brief Niszczy MenuGlowne
	 * 
	 */
	~MenuGlowne() {
		delete(this->demo);
	}

	/**
	 * @brief Rysuje obiekty znajdujace sie w menu glownym
	 * 
	 * @param target Obiekt typu RenderTarget w ktorym beda renderowane obiekty
	 */
	void draw(sf::RenderTarget* target) { /// Rysowanie obiektow na ekranie
		if (!target) target = this->window;
		demo->draw(target);
	};

	/**
	 * @brief Odswieza stan MenuGlowne
	 * 
	 * @param dtime Kontrola czasu
	 */
	void update(const float& dtime) { /// Odswiezenie stanu aktualnego "stanu"
		this->dtime = dtime;
		sprawdzMysz();
		demo->update(dtime);
	};
};

