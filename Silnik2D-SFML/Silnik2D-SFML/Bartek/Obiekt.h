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

	Obiekt(){}


	/**
	* @brief Funkcja rysuje obiekt
	*
	* @param cel Wskaznik na RenderTarget w ktorym ma odbywac sie rysowanie
	*/
	void draw(sf::RenderTarget* cel) {
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

	/**
	* @brief Funkcja ustawia 'origin' na srodku sprite'a
	*/
	void setOriginOnMiddle() {
		this->sprajt.setOrigin(sf::Vector2f(this->tekstura.getSize().x / 2, this->tekstura.getSize().y / 2));
	}

	/**
	* @brief Funkcja zwraca rozmiar sprite'a
	*/
	sf::Vector2f PobierzRozmiar() {
		return sf::Vector2f(this->sprajt.getGlobalBounds().width, this->sprajt.getGlobalBounds().height);
	}

	/**
	* @brief Funkcja zwraca rozmiar sprite'a
	*/
	sf::FloatRect pobierzPozycje() {
		return this->sprajt.getGlobalBounds();
	}

	/**
	* @brief Funkcja rozjasnia obiekt
	*
	* @param ile O ile ma byc rozjasniony obiekt
	* @param max Maksymalna wartosc rozjasnienia
	*/
	void rozjasnij(float ile, int max = 0) {
		if (max < 0) max = 0;
		if (this->sprajt.getColor().a <= max) return;
		this->sprajt.setColor(sf::Color(0, 0, 0, this->sprajt.getColor().a - ile));
	}

	/**
	* @brief Funkcja przyciemnia obiekt
	*
	* @param ile O ile ma byc przyciemniony obiekt
	* @param max Maksymalna wartosc przyciemniona
	*/
	void przyciemnij(float ile, int max = 500) {
		if (max > 255) max = 255;
		if (this->sprajt.getColor().a >= max) return;
		this->sprajt.setColor(sf::Color(0, 0, 0, this->sprajt.getColor().a + ile));
	}
};

