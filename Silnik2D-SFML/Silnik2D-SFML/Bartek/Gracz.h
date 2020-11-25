#pragma once
#include "Obiekt.h"

/**
 * @brief Klasa opisujaca gracza
 * 
 */
class Gracz :
	public Obiekt
{
private:
	/// Prostokatny ksztalt gracza (jego wymiary, ramka)
	sf::RectangleShape ksztalt; 
	/// Typ logiczny odpowiadajacy za wlaczenie i wylaczenie opcji debugu (niezaimplementowane)
	bool debug = false;
public:

	/**
	 * @brief Konsturktor obiektu Gracz
	 * 
	 * @param sciezka Sciezka do pliku z obrazem gracza
	 * @param pozycja Pozycja poczatkowa gracza
	 * @param ksztalt Obiekt RectangleShape zawierajacy ksztalt gracza
	 */
	Gracz(std::string sciezka, sf::Vector2f pozycja, sf::RectangleShape ksztalt) : Obiekt(sciezka, pozycja) {
		this->ksztalt = ksztalt;
		this->ksztalt.setPosition(pozycja);
		this->sprajt.setPosition(pozycja);
	}

	/**
	 * @brief Funkcja wlaczajaca tryb debugowania
	 * 
	 */
	void debuguj() {
		this->debug = true;
	}

	/**
	 * @brief Przeniesienie obiektu (gracza) na pozycje podana w argumencia
	 * 
	 * @param gdzie Pozycja na ktora gracz ma zostac przeniesiony
	 */
	void rusz(sf::Vector2f gdzie) { 
		this->ksztalt.setPosition(gdzie);
		this->sprajt.setPosition(gdzie);
	}

	/**
	 * @brief Rysowanie obiektu (gracza)
	 * 
	 * @param cel Obiekt typu RenderTarget wskazujacy na cel w ktorym bedzie renderowany sprite
	 */
	void draw(sf::RenderTarget* cel) { 
		cel->draw(this->sprajt);
	}
	
	/**
	 * @brief Zwraca aktualna pozycje obiektu (gracza)
	 * 
	 * @return sf::Vector2f Aktualna pozycja gracza
	 */
	sf::Vector2f pobierzPozycje() { 
		return this->ksztalt.getPosition();
	}

};

