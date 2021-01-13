#pragma once
#include "../Bartek/Obiekt.h";

class ObiektOtoczenia : public Obiekt {
	int zycie;
	double exp;
	double dmg;
	int range;
	int flag = 0;
public:
	ObiektOtoczenia(std::string sciezka, sf::Vector2f pozycja, int zycie, int exp, sf::Vector2f scale, int flag = 0, double dmg = 0, int range = 0) : Obiekt(sciezka, pozycja) {
		this->setOriginOnMiddle();
		this->przeskaluj(scale);
		this->zycie = zycie;
		this->exp = exp;
		this->flag = flag;
		this->dmg = dmg;
		this->range = range;
	}

	ObiektOtoczenia(){};
	//test
	virtual ObiektOtoczenia* clone() const {
		return new ObiektOtoczenia(*this);
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

	double zwrocDmg() {
		return this->dmg;
	}

	int zwrocRange() {
		return this->range;
	}

	void atak(Gracz* gracz, int x, int y) {
		if(this->dmg != 0) { 
			for (int i = 0; i < this->range + 1; i++) {
				for (int j = 0; j < this->range + 1; j++) {
					if (x + i == 7 && y + j == 7) {
						gracz->zadajObrazenia(this->dmg);
					}
					if (x - i == 7 && y - j == 7) {
						gracz->zadajObrazenia(this->dmg);
					}
				}
			}
		}
	}
};