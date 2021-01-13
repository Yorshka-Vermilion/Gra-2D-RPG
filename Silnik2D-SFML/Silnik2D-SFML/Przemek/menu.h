#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define ROZMIAR_OPCJI 3


/**
* @brief klasa Menu
*/
class Menu {
	/// <summary>
	/// Numer obecnie wybranej opcji
	/// </summary>
	int WybranaOpcja;
	/// <summary>
	/// Czcionka reprezentacji graficznej
	/// </summary>
	sf::Font font;
	/// <summary>
	/// Tablica opcji reprezentacji graficznych menu
	/// </summary>
	sf::Text menu[ROZMIAR_OPCJI];
	/// <summary>
	/// Wysokosc menu
	/// </summary>
	int wysokosc;
	/// <summary>
	/// Szerokosc menu
	/// </summary>
	int szerokosc;
public:
	/**
	 * @brief Konstruktor menu
	 *
	 * @param wysokosc wysokosc menu
	 * @param szerokosc szerokosc menu
	 */
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
		menu[0].setPosition(sf::Vector2f(this->szerokosc / 2, (this->wysokosc / 2) - 150));

		menu[1].setFont(font);
		menu[1].setFillColor(sf::Color::White);
		menu[1].setString("Load");
		menu[1].setCharacterSize(60);
		center = menu[1].getLocalBounds();
		menu[1].setOrigin(center.left + center.width / 2, center.top + center.height / 2);
		menu[1].setPosition(sf::Vector2f(this->szerokosc / 2, (this->wysokosc / 2)));

		menu[2].setFont(font);
		menu[2].setFillColor(sf::Color::White);
		menu[2].setString("Exit");
		menu[2].setCharacterSize(60);
		center = menu[2].getLocalBounds();
		menu[2].setOrigin(center.left + center.width / 2, center.top + center.height / 2);
		menu[2].setPosition(sf::Vector2f(this->szerokosc / 2, (this->wysokosc / 2) + 150));

		WybranaOpcja = 0;
	}

	/**
	* @brief Funkcja odpowiadajca za rysowanie menu
	* @param target odpowiada za okno w którym ma zostac narysowany obiekt
	*/
	void draw(sf::RenderTarget* target) {
		for (int i = 0; i < ROZMIAR_OPCJI; i++) {
			target->draw(menu[i]);
		}
	}

	/**
	* @brief Funkcja odpowiadajca za poruszanie sie po menu w gore
	*/
	void PoruszanieWGore() {
		if (WybranaOpcja - 1 >= 0) {
			menu[WybranaOpcja].setFillColor(sf::Color::White);
			WybranaOpcja--;
			menu[WybranaOpcja].setFillColor(sf::Color::Red);
		}
	}

	/**
	* @brief Funkcja odpowiadajca za poruszanie sie po menu w dol
	*/
	void PoruszanieWDol() {
		if (WybranaOpcja + 1 < ROZMIAR_OPCJI) {
			menu[WybranaOpcja].setFillColor(sf::Color::White);
			WybranaOpcja++;
			menu[WybranaOpcja].setFillColor(sf::Color::Red);
		}
	}
	/**
	* @brief Funkcja sprawdza czy uzytkownik wybral ktoras z opcji
	* @return int zwraca wybrana przez uzytkownika opcje
	*/
	int Nacisnieta_opcja() {
		return WybranaOpcja;
	}
};
