#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Plytka.h"
#include <math.h> 

class Mapa
{
	std::vector<std::vector<Plytka*>> plytki;
	float szerokosc;
	float wysokosc;
	float przerwa_pomiedzy;
	sf::Vector2u pozycja_poczatkowa;
	int dystans_tworzenia;
	sf::Vector2i aktualnie_podswietlona_plytka,aktualnie_zaznaczona_plytka;

public: 
	Mapa(float przerwa_pomiedzy, sf::Vector2u pozycja_poczatkowa, int dystans_tworzenia = 9) {

		this->przerwa_pomiedzy = przerwa_pomiedzy;
		this->dystans_tworzenia = dystans_tworzenia;

		for (size_t i = 0; i < dystans_tworzenia; i++) {
			this->plytki.push_back(std::vector<Plytka*>());
			for (size_t j = 0; j < dystans_tworzenia; j++) {
				this->plytki[i].push_back(new Plytka("plytka2.png", "plytka3.png", sf::Vector2f(0, 0)));
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
	}

	void ZaktualizujRozmiarPlytki() {
		if (!this->plytki.empty()) {
			this->szerokosc = this->plytki[0][0]->PobierzRozmiar().x;
			this->wysokosc = this->plytki[0][0]->PobierzRozmiar().y;
		}
	}

	void UstawPlytki() {
		PrzypiszBohatera();
		size_t i = 0;
		while (i < plytki.size()) {
			size_t j = 0;
			while (j < plytki[i].size()) {
				this->plytki[i][j]->przestaw(sf::Vector2f(((szerokosc/2) * (j + 1)) - ((szerokosc/2)*i) + this->pozycja_poczatkowa.x-(szerokosc) ,
					((wysokosc/2) * (j + 1 + i*2)) - ((wysokosc/2)*i) + this->pozycja_poczatkowa.y - (wysokosc*(plytki.size()-4))));
				j++;
			}
			i++;
		}
	}

	void PrzypiszBohatera() { // Przypisuje bohatera do plytki
		//this->plytki[dystans_tworzenia / 2 - 1, dystans_tworzenia / 2]->PrzypiszGracza();
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

				
				if (odleglosc < szerokosc/2) {
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
		
		if(prev < szerokosc/2)this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->Podswietl();
		
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

		if (aktualnie_podswietlona_plytka == sf::Vector2i(dystans_tworzenia/2-1,dystans_tworzenia/2)) {
			this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->WylaczPodswietlenie();
			Przesun(0);
		}
		else if (aktualnie_podswietlona_plytka == sf::Vector2i(dystans_tworzenia / 2 + 1, dystans_tworzenia / 2)) {
			this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->WylaczPodswietlenie();
			Przesun(1);
		}

		else if (aktualnie_podswietlona_plytka == sf::Vector2i(dystans_tworzenia / 2, dystans_tworzenia / 2-1)) {
			this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->WylaczPodswietlenie();
			Przesun(2);
		}

		else if (aktualnie_podswietlona_plytka == sf::Vector2i(dystans_tworzenia / 2, dystans_tworzenia / 2+1)) {
			this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->WylaczPodswietlenie();
			Przesun(3);
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
					this->plytki[0].push_back(new Plytka("plytka3.png", "plytka2.png", sf::Vector2f(0, 0)));
				}
			}
			else if (kierunek == 1) {
				this->plytki.erase(this->plytki.begin());
				this->plytki.push_back(std::vector<Plytka*>());
				for (size_t j = 0; j < v2s; j++) {
					this->plytki[v1s-1].push_back(new Plytka("plytka3.png", "plytka2.png", sf::Vector2f(0, 0)));
				}
			}
			else if (kierunek == 2) {
				for (size_t i = 0; i < v1s; i++) {
					this->plytki[i].pop_back();
					this->plytki[i].insert(this->plytki[i].begin(), new Plytka("plytka3.png", "plytka2.png", sf::Vector2f(0, 0)));
				}
				
			}
			else if (kierunek == 3) {
				for (size_t i = 0; i < v1s; i++) {
					this->plytki[i].erase(this->plytki[i].begin());
					this->plytki[i].push_back(new Plytka("plytka3.png", "plytka2.png", sf::Vector2f(0, 0)));
				}
			}
			UstawPlytki();
		}
		
	}
};

