#pragma once
#include "../Bartek/Obiekt.h";

class ObiektOtoczenia : public Obiekt {
	int zycie;
	double exp;
	int flag = 0;
public:
	ObiektOtoczenia(std::string sciezka, sf::Vector2f pozycja, int zycie, int exp, sf::Vector2f scale, int flag = 0) : Obiekt(sciezka, pozycja) {
		this->setOriginOnMiddle();
		this->przeskaluj(scale);
		this->zycie = zycie;
		this->exp = exp;
		this->flag = flag;
	}

	void dealDmg(int dmg) {
		if (this->zycie > 0) {
			this->zycie -= dmg;
		}
	}

	bool checkZycie() {
		if (this->zycie <= 0)
				return true;
		return false;
	}

	double returnExp() {
		return this->exp;
	}

	void draw(sf::RenderTarget* target) {
		target->draw(this->sprajt);
	}

	int zwrocFlage() {
		return this->flag;
	}

	double zwrocZycie() {
		return this->zycie;
	}

	void setZycie(double zycie) {
		if (zycie < 0) zycie = 0;
			this->zycie = zycie;
	}
};