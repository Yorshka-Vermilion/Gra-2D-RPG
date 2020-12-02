#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


/**
 * @brief Klasa opisujaca kazdy obiekt w grze
 * 
 */
class Obiekt
{
protected:
	/// Zmienna przechowujaca teksture
	sf::Texture tekstura;
public:
	/// Zmienna przechowujaca sprite
	sf::Sprite sprajt;

	/**
	 * @brief Tworzy nowy Obiekt
	 * 
	 * @param sciezka Sciezka do pliku z tekstura/obrazkiem
	 * @param pozycja Pozycja poczatkowa obiektu
	 */
	Obiekt(std::string sciezka, sf::Vector2f pozycja) {
		if (!tekstura.loadFromFile(sciezka)) {
			std::cout << "Problem z zaladowaniem tekstury : " << sciezka << std::endl;
		}
		this->sprajt.setTexture(this->tekstura);
		this->sprajt.setPosition(pozycja);
	}

	void rysuj(sf::RenderTarget* cel) {
		cel->draw(this->sprajt);
	}

	/**
	 * @brief Podmienia teksture na podana w argumencie
	 * 
	 * @param sciezka Sciezka do pliku z teksura
	 */
	void zmienTeksture(std::string sciezka) {
		if (!tekstura.loadFromFile(sciezka)) {
			std::cout << "Problem z zaladowaniem tekstury : " << sciezka << std::endl;
		}
		this->sprajt.setTexture(this->tekstura);
	}


	/**
	 * @brief Przestawia obiekt w inne miejsce
	 * 
	 * @param gdzie Gdzie ma byc przestawiony obiekt
	 */
	void przestaw(sf::Vector2f gdzie) {
		this->sprajt.setPosition(gdzie);
	}

	/**
	 * @brief Funkcja obraca obiekt
	 * 
	 * @param kat O jaki kat ma byc obrocony sprite
	 */
	void rotuj(float kat) {
		this->sprajt.setRotation(kat);
	}

	/**
	 * @brief Skaluje obiekt
	 * 
	 * @param jak O ile ma byc przeskalowany obiekt
	 */
	void przeskaluj(sf::Vector2f jak) {
		this->sprajt.setScale(jak);
	}


	sf::Vector2f PobierzRozmiar() {
		return sf::Vector2f(this->sprajt.getGlobalBounds().width, this->sprajt.getGlobalBounds().height);
	}

};

