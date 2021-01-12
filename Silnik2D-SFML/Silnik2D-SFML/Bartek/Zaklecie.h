#pragma once
#include "Animacja.h"

class Zaklecie
{
	/// Zapisuje w vectorze 'obraz' lini ktore musza byc narysowane na ekranie aby uaktywnic dane zaklecie
	std::vector<int> obraz_wzorcowy;
	double dmg;
	double mana;
	std::string nazwa;
	Animacja* animacja;
public:
	Zaklecie(std::vector<int> obraz, double dmg, double mana, std::string nazwa, Animacja *animacja) {//Jeszcze jakis wskaznik na animacje czy cos
		this->obraz_wzorcowy = obraz;
		this->dmg = dmg;
		this->mana = mana;
		this->nazwa = nazwa;
		this->animacja = animacja;
		this->animacja->setOriginOnMiddle();
	}

	bool update(sf::RenderTarget* cel, const float& dtime) {
		if (!this->animacja->koniec()) {
			this->animacja->animuj(cel, dtime);
			return false;
		}
		else return true;
	}

	bool sprawdz(std::vector<int> co) {
		if (co.size() == this->obraz_wzorcowy.size()) {
			for (size_t i = 0; i < this->obraz_wzorcowy.size(); i++) {
				if (this->obraz_wzorcowy[i] != co[i]) return false;
			}
			return true;
		}
		else return false;
	}

	std::string getNazwa() {
		return this->nazwa;
	}

	void zresetuj() {
		this->animacja->zresetuj();
	}

	void ustaw(sf::Vector2f gdzie) {
		this->animacja->rusz(gdzie);
	}

	double getDmg() {
		return this->dmg;
	}

	double getManaCost() {
		return this->mana;
	}

};

