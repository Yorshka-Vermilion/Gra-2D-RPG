#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define ROZMIAR_OPCJI 2


/**
* @brief klasa Menu
*/
class Menu {
	int WybranaOpcja;
	sf::Font font;
	sf::Text menu[ROZMIAR_OPCJI];
	int wysokosc;
	int szerokosc;
public:

	Menu(int wysokosc, int szerokosc) {
		this->wysokosc = wysokosc;
		this->szerokosc = szerokosc;
		if (!font.loadFromFile("Bandwidth 8x8.ttf"))
		{
			std::cout << "Blad!" << std::endl;
		}
		menu[0].setFont(font);
		menu[0].setFillColor(sf::Color::Red);
		menu[0].setString("Start");
		menu[0].setCharacterSize(60);
		sf::FloatRect center = menu[0].getLocalBounds();
		menu[0].setOrigin(center.left + center.width / 2, center.top + center.height / 2);
		menu[0].setPosition(sf::Vector2f(this->szerokosc / 2, (this->wysokosc / 2) - 100));

		menu[1].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[1].setString("Exit");
		menu[1].setCharacterSize(60);
		center = menu[1].getLocalBounds();
		menu[1].setOrigin(center.left + center.width / 2, center.top + center.height / 2);
		menu[1].setPosition(sf::Vector2f(this->szerokosc / 2, (this->wysokosc / 2)+100));
		

		WybranaOpcja = 0;
	}
	
	void draw(sf::RenderTarget* target) {
		for (int i = 0; i < ROZMIAR_OPCJI; i++) {
			target->draw(menu[i]);
		}		
	}

	void PoruszanieWGore() {
		if (WybranaOpcja - 1 >= 0) {
			menu[WybranaOpcja].setFillColor(sf::Color::White);
			WybranaOpcja--;
			menu[WybranaOpcja].setFillColor(sf::Color::Red);
		}
	}
	
	void PoruszanieWDol() {
		if (WybranaOpcja + 1 < ROZMIAR_OPCJI) {
			menu[WybranaOpcja].setFillColor(sf::Color::White);
			WybranaOpcja++;
			menu[WybranaOpcja].setFillColor(sf::Color::Red);
		}
	}
	int Nacisnieta_opcja() {
		return WybranaOpcja;
	}
};
