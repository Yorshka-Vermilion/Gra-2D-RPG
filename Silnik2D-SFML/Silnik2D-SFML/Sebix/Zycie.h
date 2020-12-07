#pragma once
#include "../Bartek/Obiekt.h";

class Zycie : public Obiekt {
	bool active = true;
public:
	Zycie(std::string sciezka, sf::Vector2f pozycja) : Obiekt(sciezka, pozycja) {
		this->sprajt.setPosition(pozycja);
	}

	void draw(sf::RenderTarget* cel) {
			cel->draw(this->sprajt);
	}

	void zmienStan() {
		if (this->active == false) {
			this->active = true;
			this->zmienTeksture("life.png");
		}
		else {
			this->active = false;
			this->zmienTeksture("emptylife.png");
		}
	}

	bool sprawdzStan() {
		return this->active;
	}
};



