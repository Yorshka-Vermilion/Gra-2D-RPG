#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Plytka.h"
#include "Gracz.h"

class Mapa
{
	float szerokosc;
	float wysokosc;
	float przerwa_pomiedzy;
	sf::Vector2u pozycja_poczatkowa;
	int dystans_tworzenia;
	sf::Vector2i aktualnie_podswietlona_plytka, aktualnie_zaznaczona_plytka;
	Gracz* gracz;
	//Test
	int random;
	std::string obr[4] = { "plytka1.png","plytka2.png" ,"plytka3.png" ,"plytka4.png" };

public:
	std::vector<std::vector<Plytka*>> plytki;

	Mapa(float przerwa_pomiedzy, sf::Vector2u pozycja_poczatkowa,Gracz* gracz, int dystans_tworzenia = 15) {
		srand(time(NULL));
		this->przerwa_pomiedzy = przerwa_pomiedzy;
		this->dystans_tworzenia = dystans_tworzenia;
		this->gracz = gracz;

		
		for (size_t i = 0; i < dystans_tworzenia; i++) {
			this->plytki.push_back(std::vector<Plytka*>());
			for (size_t j = 0; j < dystans_tworzenia; j++) {
				this->random = rand() % 3;
				//Test
				this->plytki[i].push_back(new Plytka(obr[random], obr[3], sf::Vector2f(0, 0)));
				//this->plytki[i].push_back(new Plytka("plytka2.png","plytka3.png", sf::Vector2f(0, 0)));
			}
		}

		//Ustawia poczatkowa pozycje na srodku ekranu
		this->pozycja_poczatkowa = pozycja_poczatkowa;
		this->pozycja_poczatkowa.x = this->pozycja_poczatkowa.x / 2;
		this->pozycja_poczatkowa.y = this->pozycja_poczatkowa.y / 2;

		//Laduje teksture podswietlenia
		this->aktualnie_podswietlona_plytka.x = -1;

		//RotujPlytki();
		ZaktualizujRozmiarPlytki();
		UstawPlytki();

		//Test
		for (size_t i = 0; i < dystans_tworzenia; i++) {
			for (size_t j = 0; j < dystans_tworzenia; j++) {
				this->random = 1 + rand() % 100;
				if (random % 20 == 0) {
					if (i == this->plytki.size() / 2 && j == this->plytki[this->plytki.size() / 2].size() / 2) return;
					PrzypiszObiekt("beczka.png", i, j, 100, random*5, sf::Vector2f(0.15, 0.15),2); //<---- zmiena flagi - ostatnia liczba
				}
			}
		}

	}

	void ZaktualizujRozmiarPlytki() {
		if (!this->plytki.empty()) {
			this->szerokosc = this->plytki[0][0]->PobierzRozmiar().x;
			this->wysokosc = this->plytki[0][0]->PobierzRozmiar().y;
		}
	}

	void UstawPlytki() {
		size_t i = 0;
		while (i < plytki.size()) {
			size_t j = 0;
			while (j < plytki[i].size()) {
				this->plytki[i][j]->setOriginOnMiddle();
				this->plytki[i][j]->przestaw(sf::Vector2f(((szerokosc/2) * (j + 1)) - ((szerokosc/2)*i) + this->pozycja_poczatkowa.x-(szerokosc) ,
					((wysokosc/2) * (j + 1 + i*2)) - ((wysokosc/2)*i) + this->pozycja_poczatkowa.y - (wysokosc*(plytki.size()-4))));
				this->plytki[i][j]->aktualizujObiekt();
				j++;
			}
			i++;
		}
		PrzypiszBohatera();
	}

	void PrzypiszObiekt(std::string sciezka, int x, int y, int zycie, int exp, sf::Vector2f scale, int flag = 0) {
		this->plytki[x][y]->PrzypiszObiekt(new ObiektOtoczenia(sciezka, sf::Vector2f(0, 0), zycie, exp, scale, flag));
	}

	void PrzypiszBohatera() { // Przypisuje bohatera do plytki
		this->plytki[this->plytki.size() / 2][this->plytki[this->plytki.size() / 2].size() / 2]->PrzypiszGracza(this->gracz);
	}

	void RotujPlytki() {
		size_t i = 0;
		while (i < plytki.size()) {
			size_t j = 0;
			while (j < plytki[i].size()) {
				this->plytki[i][j]->rotuj(45);
				j++;
			}
			i++;
		}
	}

	void draw(sf::RenderTarget* cel) {
		size_t i = 0;
		while (i < plytki.size()) {
			size_t j = 0;
			while (j < plytki[i].size()) {
					this->plytki[i][j]->draw(cel);
					j++;
			}
			i++;
		}
	}

	void update() {
		size_t i = 0;
		while (i < plytki.size()) {
			size_t j = 0;
			while (j < plytki[i].size()) {
				this->gracz->dodajExp(this->plytki[i][j]->update());
				j++;
			}
			i++;
		}
	}

	void podswietlKafelki(sf::Vector2f pozycjaMyszy) {
		size_t i = 0;
		if (this->aktualnie_podswietlona_plytka.x >= 0) {
			this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->WylaczPodswietlenie();
			this->aktualnie_podswietlona_plytka.x = -1;
		}

		float prev = szerokosc * 2;
		while (i < plytki.size()) {
			size_t j = 0;

			while (j < plytki[i].size()) {
				sf::FloatRect FR = this->plytki[i][j]->pobierzPozycje();

				sf::Vector2f srodek;
				srodek.x = FR.left + (FR.width / 2);
				srodek.y = FR.top + (FR.height / 2);

				float odleglosc = std::sqrt(pow(pozycjaMyszy.x - srodek.x, 2) + pow(pozycjaMyszy.y - srodek.y, 2));


				if (odleglosc < szerokosc / 2) {
					if (odleglosc < prev) {
						//this->plytki[i][j]->Podswietl();
						prev = odleglosc;
						this->aktualnie_podswietlona_plytka = sf::Vector2i(i, j);
						//return;
					}
				};
				j++;
			}
			i++;
		}

		if (prev < szerokosc / 2)this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->Podswietl();

	}

	void zaznaczKafelek() {
		if (this->aktualnie_zaznaczona_plytka.x >= 0)this->plytki[aktualnie_zaznaczona_plytka.x][aktualnie_zaznaczona_plytka.y]->WylaczPodswietlenie(true);
		if (this->aktualnie_podswietlona_plytka.x >= 0) {
			this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->Zaznacz();
			this->aktualnie_zaznaczona_plytka = this->aktualnie_podswietlona_plytka;
		}
	}

	void Rusz() {
		if (this->aktualnie_zaznaczona_plytka.x >= 0)this->plytki[aktualnie_zaznaczona_plytka.x][aktualnie_zaznaczona_plytka.y]->WylaczPodswietlenie(true);
		if (this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocDostepnosc() == true){
			if (this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocObiekt()->zwrocFlage() == 2) {
				this->gracz->zadajObrazenia(this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocObiekt()->zwrocZycie());
				this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocObiekt()->setZycie(0);
			}
			if (aktualnie_podswietlona_plytka == sf::Vector2i(dystans_tworzenia / 2 - 1, dystans_tworzenia / 2)){
				this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->WylaczPodswietlenie();
				Przesun(0);
			}
			else if (aktualnie_podswietlona_plytka == sf::Vector2i(dystans_tworzenia / 2 + 1, dystans_tworzenia / 2)) {
				this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->WylaczPodswietlenie();
				Przesun(1);
			}

			else if (aktualnie_podswietlona_plytka == sf::Vector2i(dystans_tworzenia / 2, dystans_tworzenia / 2 - 1)) {
				this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->WylaczPodswietlenie();
				Przesun(2);
			}

			else if (aktualnie_podswietlona_plytka == sf::Vector2i(dystans_tworzenia / 2, dystans_tworzenia / 2 + 1)) {
				this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->WylaczPodswietlenie();
				Przesun(3);
			}
		}
	}

	void Przesun(int kierunek) { // 0 lewo, 1 prawo, 2 gora, 3 dol
		if (!this->plytki.empty()) {
			size_t v1s = dystans_tworzenia;
			size_t v2s = dystans_tworzenia;
			if (kierunek == 0) {
				this->plytki.pop_back();
				this->plytki.insert(this->plytki.begin(), std::vector<Plytka*>());
				for (size_t j = 0; j < v2s; j++) {
					this->random = rand() % 3;
					this->plytki[0].push_back(new Plytka(obr[random], obr[3], sf::Vector2f(0, 0)));
				}
			}
			else if (kierunek == 1) {
				this->plytki.erase(this->plytki.begin());
				this->plytki.push_back(std::vector<Plytka*>());
				for (size_t j = 0; j < v2s; j++) {
					this->random = rand() % 3;
					this->plytki[v1s-1].push_back(new Plytka(obr[random], obr[3], sf::Vector2f(0, 0)));
				}
			}
			else if (kierunek == 2) {
				for (size_t i = 0; i < v1s; i++) {
					this->plytki[i].pop_back();
					this->random = rand() % 3;
					this->plytki[i].insert(this->plytki[i].begin(), new Plytka(obr[3], obr[random + 1], sf::Vector2f(0, 0)));
				}
				
			}
			else if (kierunek == 3) {
				for (size_t i = 0; i < v1s; i++) {
					this->random = rand() % 3;
					this->plytki[i].erase(this->plytki[i].begin());
					this->plytki[i].push_back(new Plytka(obr[random], obr[3], sf::Vector2f(0, 0)));
				}
			}
			UstawPlytki();
		}
		
	}

	int zwrocWielkoscMapy() {
		return this->dystans_tworzenia;
	}

	Plytka* zwrocAktualnieZaznaczona() {
		return this->plytki[this->aktualnie_zaznaczona_plytka.x][this->aktualnie_zaznaczona_plytka.y];
	}
};

