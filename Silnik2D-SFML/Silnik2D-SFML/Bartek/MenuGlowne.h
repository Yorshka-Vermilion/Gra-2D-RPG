#pragma once
#include "Animacja.h"
#include "../Sebix.h"
#include "../Przemek/menu.h"
#include "Gracz.h"
#include "ObslugaRuchuGracza.h"
#include "Obiekt.h"
#include "../Sebix/Creator.h"
#include "Gra.h"

/**
 * @brief Klasa opisujaca MenuGlowne
 *
 */
class MenuGlowne : public Stan
{
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
		this->menu = new Menu(window->getSize().y, window->getSize().x);
	}

	/**
	 * @brief Niszczy MenuGlowne
	 *
	 */
	~MenuGlowne() {

	}

	/**
	* @brief Funkcja obsluguje poruszanie sie po menu za pomoca strzalki w gore i w dol
	*/
	void Poruszanie_po_menu() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
			menu->PoruszanieWGore();
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
			menu->PoruszanieWDol();
		}
	}

	/**
	* @brief Funkcja obsluguje wybieranie zaznaczonej opcji w menu
	*/
	void Wybieranie_w_menu() {
		if (sf::Event::KeyPressed) {
			if (event->key.code == sf::Keyboard::Key::Enter) {
				if (menu->Nacisnieta_opcja() == 0) {
					this->stos->push(new Creator(window, stos, event));
				}
				else if (menu->Nacisnieta_opcja() == 1) {
					std::ifstream file;
					file.open("Save.txt", std::ios::in | std::ios::out | std::ios::binary);

					if (file.is_open()) {

						std::string text[255];
						int i = 0;
						while (!file.eof()) {
							std::getline(file, text[i]);
							i++;
						}

						Gracz* gracz = new Gracz("H11.png", sf::Vector2f(200, 200), 100, 300, 1000);
						gracz->zycie = atof(text[0].c_str());
						gracz->maxZycie = atof(text[1].c_str());
						gracz->mana = atof(text[2].c_str());
						gracz->maxMana = atof(text[3].c_str());
						gracz->level = atoi(text[4].c_str());
						gracz->exp = atof(text[5].c_str());
						gracz->maxExp = atof(text[6].c_str());
						gracz->nazwa = text[7].c_str();
						gracz->statystyki->sila = atoi(text[8].c_str());
						gracz->statystyki->magicDmg = atoi(text[9].c_str());
						gracz->statystyki->inteligencja = atoi(text[10].c_str());
						gracz->statystyki->dostepnePunkty = atoi(text[11].c_str());
						gracz->sprajt.setColor(sf::Color(atoi(text[12].c_str()), atoi(text[13].c_str()), atoi(text[14].c_str())));
						Gra* gra = new Gra(window, stos, event, gracz);
						this->stos->push(gra);
					}
				}
				else if (menu->Nacisnieta_opcja() == 2) {
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
		while (this->window->pollEvent(*this->event)) {
			Poruszanie_po_menu();
		}
		Wybieranie_w_menu();
		sprawdzMysz();
	};
};

