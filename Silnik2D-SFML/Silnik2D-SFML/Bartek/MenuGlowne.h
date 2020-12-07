#pragma once
#include "Animacja.h"
#include "../Sebix.h"
#include "../Przemek/menu.h"
#include "Gracz.h"
#include "ObslugaRuchuGracza.h"
#include "Obiekt.h"
#include "Gra.h"


/**
 * @brief Klasa opisujaca MenuGlowne
 *
 */
class MenuGlowne : public Stan
{
	///Obiekt Demo

public:
	Menu* menu;

	/**
	 * @brief Tworzy nowy obiekt MenuGlowne
	 *
	 * @param window Okno
	 * @param stos Stos stanow
	 * @param event Eventy
	 */
	MenuGlowne(sf::RenderWindow* window, std::stack<Stan*>* stos, sf::Event* event) : Stan(window, stos, event) {
		this->menu = new Menu(window->getSize().y,window->getSize().x);
	
	}

	/**
	 * @brief Niszczy MenuGlowne
	 *
	 */
	~MenuGlowne() {

	}

	void Poruszanie_po_menu() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
			menu->PoruszanieWGore();
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
			menu->PoruszanieWDol();
		}
	}

	void Wybieranie_w_menu() {
		if (sf::Event::KeyPressed) {
			if (event->key.code == sf::Keyboard::Key::Enter) {
				if (menu->Nacisnieta_opcja() == 0) {
					this->stos->push(new Gra(window, stos, event));
				}
				else if (menu->Nacisnieta_opcja() == 1) {
					window->close();
				}
			}
		}
	}

	/**
	 * @brief Rysuje obiekty znajdujace sie w menu glownym
	 *
	 * @param target Obiekt typu RenderTarget w ktorym beda renderowane obiekty
	 */
	void draw(sf::RenderTarget* target) { /// Rysowanie obiektow na ekranie
		if (!target) target = this->window;
		this->menu->draw(target);
	};

	/**
	 * @brief Odswieza stan MenuGlowne
	 *
	 * @param dtime Kontrola czasu
	 */
	void update(const float& dtime) { /// Odswiezenie stanu aktualnego "stanu"
		this->dtime = dtime;
		Poruszanie_po_menu();
		Wybieranie_w_menu();
		sprawdzMysz();
	};
};

