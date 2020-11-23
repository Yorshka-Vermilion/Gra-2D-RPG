#pragma once
#include "Obiekt.h"
class Gracz :
	public Obiekt
{
private:
	sf::RectangleShape ksztalt;
	bool debug = false;
public:
	Gracz(std::string sciezka, sf::Vector2f pozycja, sf::RectangleShape ksztalt) : Obiekt(sciezka, pozycja) {
		this->ksztalt = ksztalt;
		this->ksztalt.setPosition(pozycja);
		this->sprajt.setPosition(pozycja);
	}

	void debuguj() {
		this->debug = true;
	}

	void rusz(sf::Vector2f gdzie) {
		this->ksztalt.setPosition(gdzie);
		this->sprajt.setPosition(gdzie);
	}

	void draw(sf::RenderTarget* cel) {
		cel->draw(this->sprajt);
	}

	sf::Vector2f pobierzPozycje() {
		return this->ksztalt.getPosition();
	}

};

