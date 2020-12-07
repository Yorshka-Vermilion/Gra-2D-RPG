#pragma once
#include "../Bartek/Obiekt.h";

class Mana : public Obiekt {
	bool active = true;
public:
	Mana(std::string sciezka, sf::Vector2f pozycja) : Obiekt(sciezka, pozycja) {
		this->sprajt.setPosition(pozycja);
	}

	void draw(sf::RenderTarget* cel) {
			cel->draw(this->sprajt);
	}

	void zmienStan() {
		if (this->active == false) {
			this->active = true;
			this->zmienTeksture("mana.png");
		}
		else {
			this->active = false;
			this->zmienTeksture("emptymana.png");
		}
	}

	bool sprawdzStan() {
		return this->active;
	}
};



