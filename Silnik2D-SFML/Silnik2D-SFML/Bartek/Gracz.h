#pragma once
#include "Obiekt.h"
class Gracz :
	public Obiekt
{
private:
	sf::RectangleShape ksztalt; /// Prostokatny ksztalt gracza (jego wymiary, ramka)
	bool debug = false; /// Typ logiczny odpowiadajacy za wlaczenie i wylaczenie opcji debugu (niezaimplementowane)
public:
	Gracz(std::string sciezka, sf::Vector2f pozycja, sf::RectangleShape ksztalt) : Obiekt(sciezka, pozycja) {
		this->ksztalt = ksztalt;
		this->ksztalt.setPosition(pozycja);
		this->sprajt.setPosition(pozycja);
	}

	void debuguj() { /// Metoda sluzaca do wlaczenia opcji debugowania
		this->debug = true;
	}

	void rusz(sf::Vector2f gdzie) { /// Przeniesienie obiektu (gracza) na pozycje podana w argumencia
		this->ksztalt.setPosition(gdzie);
		this->sprajt.setPosition(gdzie);
	}

	void draw(sf::RenderTarget* cel) { /// Rysowanie obiektu (gracza)
		cel->draw(this->sprajt);
	}
	
	sf::Vector2f pobierzPozycje() { /// Zwraca aktualna pozycje obiektu (gracza)
		return this->ksztalt.getPosition();
	}

};

