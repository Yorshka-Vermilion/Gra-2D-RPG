#pragma once
#include "Obiekt.h"
#include "Gracz.h"
#include "../Sebix/ObiektOtoczenia.h"

class Plytka : public Obiekt
{
	/// Zmienna sluzaca do sprawdzania czy mozna przejsc na plytke
	bool dostepna = true;
	sf::Texture podswietlenie, zaznaczenie;
	bool zaznaczona = false;
	ObiektOtoczenia* otoczenie = nullptr;

public:
	Plytka(std::string sciezka, std::string sciezka_podswietlenia, sf::Vector2f pozycja) : Obiekt(sciezka, pozycja) {
		if (!this->podswietlenie.loadFromFile(sciezka_podswietlenia)) {
			std::cout << "Blad ladowania tekstury podswietlenia plytki" << std::endl;
		}

		if (!this->zaznaczenie.loadFromFile("plytka4.png")) {
			std::cout << "Blad ladowania tekstury podswietlenia plytki" << std::endl;
		}

	}

	~Plytka() {
		delete(this->otoczenie);
	}

	void draw(sf::RenderTarget* cel) {
		cel->draw(this->sprajt);
		if(this->otoczenie != nullptr)
			this->otoczenie->draw(cel);
	}

	double update() {
		if (this->otoczenie != nullptr) {
			if (this->otoczenie->checkZycie() == true){
				double returnExpValue = this->otoczenie->returnExp();
				this->ZmienDostepnosc(true);
			    delete(this->otoczenie);
				this->otoczenie = nullptr;
				return returnExpValue;
			}
		}
		return 0;
	}

	void PrzypiszGracza(Gracz* gracz) {
		gracz->rusz(sf::Vector2f(this->sprajt.getPosition().x, this->sprajt.getPosition().y - this->tekstura.getSize().y / 4));
	}

	void PrzypiszObiekt(ObiektOtoczenia* obiekt) {
		this->otoczenie = obiekt;
		this->otoczenie->przestaw(sf::Vector2f(this->sprajt.getPosition().x, this->sprajt.getPosition().y - this->tekstura.getSize().y / 4));
		if(this->otoczenie->zwrocFlage() == 1) this->ZmienDostepnosc(false);
	}

	// Ustawia zmienna dostepna.
	void ZmienDostepnosc(bool jak) {
		this->dostepna = jak;
	}

	void Podswietl() {
		if (!this->zaznaczona)this->sprajt.setTexture(this->podswietlenie);
	}

	void WylaczPodswietlenie(bool force = false) {
		if (force || !this->zaznaczona) {
			this->sprajt.setTexture(this->tekstura);
			this->zaznaczona = false;
		}
	}

	void Zaznacz() {
		if (!zaznaczona) {
			this->sprajt.setTexture(this->zaznaczenie);
			this->zaznaczona = true;
		}
		else WylaczPodswietlenie(true);

	}

	ObiektOtoczenia* zwrocObiekt() {
		if(this->otoczenie != nullptr)
			return this->otoczenie;
	}

	bool zwrocDostepnosc() {
		return this->dostepna;
	}

	void aktualizujObiekt() {
		if(this->otoczenie)
			this->otoczenie->przestaw(sf::Vector2f(this->sprajt.getPosition().x, this->sprajt.getPosition().y - this->tekstura.getSize().y / 4));
	}

};