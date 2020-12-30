#pragma once
#include "Obiekt.h"
#include "Gracz.h"

class Plytka : public Obiekt
{
	/// Zmienna sluzaca do sprawdzania czy mozna przejsc na plytke
	bool dostepna = true;
	sf::Texture podswietlenie, zaznaczenie;
	bool zaznaczona = false;

public:
	Plytka(std::string sciezka, std::string sciezka_podswietlenia, sf::Vector2f pozycja) : Obiekt(sciezka, pozycja) {
		if (!this->podswietlenie.loadFromFile(sciezka_podswietlenia)) {
			std::cout << "Blad ladowania tekstury podswietlenia plytki" << std::endl;
		}

		if (!this->zaznaczenie.loadFromFile("plytka4.png")) {
			std::cout << "Blad ladowania tekstury podswietlenia plytki" << std::endl;
		}

	}



	void PrzypiszGracza(Gracz* gracz) {
		gracz->rusz(sf::Vector2f(this->sprajt.getPosition().x, this->sprajt.getPosition().y - this->tekstura.getSize().y / 4));
		this->ZmienDostepnosc(false);
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

};

