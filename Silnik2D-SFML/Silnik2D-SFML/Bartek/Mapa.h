#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Sebix/ObiektOtoczenia.h"
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
	std::string plyty[4] = { "Grass1.png","Grass2.png" ,"Grass3.png" ,"podswietlenie.png" };
	//Test
	ObiektOtoczenia* otoczenie[4] = {
		 new ObiektOtoczenia("beczka.png", sf::Vector2f(0, 0), 1 + rand() % 100, 1 + rand() % 100, sf::Vector2f(0.15, 0.15), 2),
		 new ObiektOtoczenia("ghost.png", sf::Vector2f(0, 0), 1 + rand() % 100, 1 + rand() % 100, sf::Vector2f(2, 2),0, 1 + rand() % 25, 3),
		 new ObiektOtoczenia("rock.png", sf::Vector2f(0, 0), 1 + rand() % 100, 1 + rand() % 100, sf::Vector2f(3, 3), 1),
		 new ObiektOtoczenia("skeleton.png", sf::Vector2f(0, 0), 1 + rand() % 100, 1 + rand() % 100, sf::Vector2f(2, 2), 1, 1 + rand() % 25, 1)
	};

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
				//Test
				this->plytki[i].push_back(new Plytka(plyty[rand() % 3], plyty[3], sf::Vector2f(0, 0)));
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
				if ((1 + rand()%100)%50 == 0) {
					if (i == this->plytki.size() / 2 && j == this->plytki[this->plytki.size() / 2].size() / 2) return;
					ObiektOtoczenia* tmp = this->otoczenie[rand()%4]->clone();
					PrzypiszObiekt(tmp,i,j);
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

	void PrzypiszObiekt(ObiektOtoczenia* obiekt, int x, int y) {
		this->plytki[x][y]->PrzypiszObiekt(obiekt);
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

	void animuj(sf::RenderTarget* okno, const float& dtime) {
		size_t i = 0;
		while (i < plytki.size()) {
			size_t j = 0;
			while (j < plytki[i].size()) {
				this->plytki[i][j]->animuj(okno, dtime);
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

	bool Rusz() {
		if (this->aktualnie_zaznaczona_plytka.x >= 0)this->plytki[aktualnie_zaznaczona_plytka.x][aktualnie_zaznaczona_plytka.y]->WylaczPodswietlenie(true);
		if (this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocDostepnosc() == true){
			if (aktualnie_podswietlona_plytka == sf::Vector2i(dystans_tworzenia / 2 - 1, dystans_tworzenia / 2)){
				this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->WylaczPodswietlenie();
				if (NULL != this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocObiekt()) {
					if (this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocObiekt()->zwrocFlage() == 2) {
						this->gracz->zadajObrazenia(this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocObiekt()->zwrocZycie());
						this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocObiekt()->setZycie(0);
					}
				}
				Przesun(0);
				return true;
			}

			else if (aktualnie_podswietlona_plytka == sf::Vector2i(dystans_tworzenia / 2 + 1, dystans_tworzenia / 2)) {
				this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->WylaczPodswietlenie();
				if (NULL != this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocObiekt()) {
					if (this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocObiekt()->zwrocFlage() == 2) {
						this->gracz->zadajObrazenia(this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocObiekt()->zwrocZycie());
						this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocObiekt()->setZycie(0);
					}
				}
				Przesun(1);
				return true;
			}

			else if (aktualnie_podswietlona_plytka == sf::Vector2i(dystans_tworzenia / 2, dystans_tworzenia / 2 - 1)) {
				this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->WylaczPodswietlenie();
				if (NULL != this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocObiekt()) {
					if (this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocObiekt()->zwrocFlage() == 2) {
						this->gracz->zadajObrazenia(this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocObiekt()->zwrocZycie());
						this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocObiekt()->setZycie(0);
					}
				}
				Przesun(2);
				return true;
			}

			else if (aktualnie_podswietlona_plytka == sf::Vector2i(dystans_tworzenia / 2, dystans_tworzenia / 2 + 1)) {
				this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->WylaczPodswietlenie();
				if (NULL != this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocObiekt()) {
					if (this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocObiekt()->zwrocFlage() == 2) {
						this->gracz->zadajObrazenia(this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocObiekt()->zwrocZycie());
						this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->zwrocObiekt()->setZycie(0);
					}
				}
				Przesun(3);
				return true;
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
					this->plytki[0].push_back(new Plytka(plyty[rand() % 3], plyty[3], sf::Vector2f(0, 0)));
					if (rand() % 50 == 0) {
						ObiektOtoczenia* tmp = this->otoczenie[rand() % 4]->clone();
						PrzypiszObiekt(tmp, 0, j);
					}
				}
			}
			else if (kierunek == 1) {
				this->plytki.erase(this->plytki.begin());
				this->plytki.push_back(std::vector<Plytka*>());
				for (size_t j = 0; j < v2s; j++) {
					this->plytki[v1s-1].push_back(new Plytka(plyty[rand() % 3], plyty[3], sf::Vector2f(0, 0)));
					if (rand() % 50 == 0) {
						ObiektOtoczenia* tmp = this->otoczenie[rand() % 4]->clone();
						PrzypiszObiekt(tmp, v2s-1, j);
					}
				}
			}
			else if (kierunek == 2) {
				for (size_t i = 0; i < v1s; i++) {
					this->plytki[i].pop_back();
					this->plytki[i].insert(this->plytki[i].begin(), new Plytka(plyty[rand()%3], plyty[3], sf::Vector2f(0, 0)));
					if (rand() % 50 == 0) {
						ObiektOtoczenia* tmp = this->otoczenie[rand() % 4]->clone();
						PrzypiszObiekt(tmp, i, 0);
					}
				}
				
			}
			else if (kierunek == 3) {
				for (size_t i = 0; i < v1s; i++) {
					this->plytki[i].erase(this->plytki[i].begin());
					this->plytki[i].push_back(new Plytka(plyty[rand() % 3], plyty[3], sf::Vector2f(0, 0)));
					if (rand() % 50 == 0) {
						ObiektOtoczenia* tmp = this->otoczenie[rand() % 4]->clone();
						PrzypiszObiekt(tmp, i, v1s-1);
					}
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

	int zwrocDystansTworzenia() {
		return this->dystans_tworzenia;
	}
};

