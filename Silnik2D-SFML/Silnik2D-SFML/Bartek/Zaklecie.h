#pragma once
class Zaklecie
{
	std::vector<int> obraz;
	double dmg;
	double mana;
	std::string nazwa;
public:
	Zaklecie(std::vector<int> obraz, double dmg, double mana, std::string nazwa) {//Jeszcze jakis wskaznik na animacje czy cos
		this->obraz = obraz;
		this->dmg = dmg;
		this->mana = mana;
		this->nazwa = nazwa;
	}

	bool sprawdz(std::vector<int> co) {
		if (co.size() == this->obraz.size()) {
			for (size_t i = 0; i < this->obraz.size(); i++) {
				if (this->obraz[i] != co[i]) return false;
			}
			return true;
		}
		else return false;
	}

	std::string getNazwa() {
		return this->nazwa;
	}

	double getDmg() {
		return this->dmg;
	}

	double getManaCost() {
		return this->mana;
	}

};

