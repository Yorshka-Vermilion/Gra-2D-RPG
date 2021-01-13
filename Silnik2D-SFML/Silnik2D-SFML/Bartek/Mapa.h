#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../Sebix/ObiektOtoczenia.h"
#include "Plytka.h"
#include "Gracz.h"

class Mapa
{
	/// Szerokosc kafelka
	float szerokosc;
	/// Wysokosc kafelka
	float wysokosc;
	/// Przerwa pomiedzy kafelkami
	float przerwa_pomiedzy;
	/// Index x i y kafelka na ktorym znajduje sie gracz
	sf::Vector2u pozycja_poczatkowa;
	/// Dystans tworzenia mapy, ilosc kafelkow jednoczesnie znajdujaca sie na mapie
	int dystans_tworzenia;
	/// Index x i y aktualnie podswietlonej plytki
	sf::Vector2i aktualnie_podswietlona_plytka;
	/// Index x i y aktualnie zaznaczonej plytki
	sf::Vector2i aktualnie_zaznaczona_plytka;
	/// Wskaznik na gracza
	Gracz* gracz;
	/// Tablica sciezek do plikow z teksturami mapy
	std::string plyty[4] = { "Grass1.png","Grass2.png" ,"Grass3.png" ,"podswietlenie.png" };
	/// Tablica wskaznikow na gotowe obiekty otoczenia
	ObiektOtoczenia* otoczenie[5] = {
		 new ObiektOtoczenia("beczka.png", sf::Vector2f(0, 0), 1 + rand() % 100, 1 + rand() % 100, sf::Vector2f(0.15, 0.15), 2),
		 new ObiektOtoczenia("ghost.png", sf::Vector2f(0, 0), 1 + rand() % 100, 1 + rand() % 100, sf::Vector2f(2, 2),0, 1 + rand() % 25, 3),
		 new ObiektOtoczenia("rock.png", sf::Vector2f(0, 0), 1 + rand() % 100, 1 + rand() % 100, sf::Vector2f(3, 3), 1),
		 new ObiektOtoczenia("skeleton.png", sf::Vector2f(0, 0), 1 + rand() % 100, 1 + rand() % 100, sf::Vector2f(2, 2), 1, 1 + rand() % 25, 1),
		 new ObiektOtoczenia("H12.png", sf::Vector2f(0, 0),1000,1000, sf::Vector2f(2, 2), 1, 100, 0,true)
	};

public:
	/// Vector z vectorami z wskaznikami na plytki, przechowuje cala mape
	std::vector<std::vector<Plytka*>> plytki;
	/**
	 * @brief Konstruktor mapy
	 *
	 * @param przerwa_pomiedzy Przerwa pomiedzy plytkami
	 * @param pozycja_poczatkowa Pozycja poczatkowa gracza
	 * @param gracz Wskaznik na gracza
	 * @param dystans_tworzenia Ilosc kafelkow mapy na osi x i y ktore beda przechowywane w vectorze plytki
	 */
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
		PrzypiszObiekt(otoczenie[4], 4, 4);
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
	/**
	 * @brief Funkcja sprawdzajaca jaki rozmiar maja wgrane plytki
	 *
	 */
	void ZaktualizujRozmiarPlytki() {
		if (!this->plytki.empty()) {
			this->szerokosc = this->plytki[0][0]->PobierzRozmiar().x;
			this->wysokosc = this->plytki[0][0]->PobierzRozmiar().y;
		}
	}
	/**
	 * @brief Funkcja ustawiajaca plytki w odpowiednich miejscach na ekranie
	 *
	 */
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
	/**
	 * @brief Funkcja przypisuje obiekt otoczenia do dane plytki
	 *
	 * @param sciezka Sciezka do pliku z tekstura
	 * @param x Index x w vectorze plytki, wskazuje na plytke do ktorej ma byc przypisany obiekt
	 * @param y Index y w vectorze plytki, wskazuje na plytke do ktorej ma byc przypisany obiekt
	 * @param zycie Zycie obiektu
	 * @param scale Skala obiektu
	 * @param flag Reprezentuje status obiektu (0-przenikalny, 1-nieprzenikalny, 2-zniszczalny)
	 */
	void PrzypiszObiekt(std::string sciezka, int x, int y, int zycie, int exp, sf::Vector2f scale, int flag = 0) {
		this->plytki[x][y]->PrzypiszObiekt(new ObiektOtoczenia(sciezka, sf::Vector2f(0, 0), zycie, exp, scale, flag));
	}
	/**
	 * @brief Funkcja przypisujaca obiekt otoczenia do danej plytki
	 *
	 * @param obiekt Wskaznik na ObiektOtoczenia do przypisania
	 * @param x Index x w vectorze plytki, wskazuje na plytke do ktorej ma byc przypisany obiekt
	 * @param y Index y w vectorze plytki, wskazuje na plytke do ktorej ma byc przypisany obiekt
	 */
	void PrzypiszObiekt(ObiektOtoczenia* obiekt, int x, int y) {
		this->plytki[x][y]->PrzypiszObiekt(obiekt);
	}
	/**
	 * @brief Przypisuje bohatera do plytki
	 *
	 */
	void PrzypiszBohatera() { // Przypisuje bohatera do plytki
		this->plytki[this->plytki.size() / 2][this->plytki[this->plytki.size() / 2].size() / 2]->PrzypiszGracza(this->gracz);
	}

	/**
	 * @brief Rysowanie wszystkich elementow mapy
	 *
	 * @param cel Obiekt typu RenderTarget wskazujacy na cel rysowania
	 */
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
	
	/**
	 * @brief Funkcja obsluguje animacje obiektow znajdujacych sie na plytkach
	 *
	 * @param cel Obiekt typu RenderTarget wskazujacy na cel rysowania
	 * @param dtime Delta czasu (timer)
	 */
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

	/**
	 * @brief Aktualizowanie stanu mapy i kazdego kafelka
	 *
	 */
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

	/**
	 * @brief Podswietlanie kafelka nad ktorym znajduje sie mysz
	 *
	 * @param pozycjaMyszy Vector2f przechowujacy pozycje myszy na ekranie
	 */
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

	/**
	 * @brief Zaznaczanie kafelka nad ktorym aktualnie znajduje sie mysz
	 *
	 */
	void zaznaczKafelek() {
		if (this->aktualnie_zaznaczona_plytka.x >= 0)this->plytki[aktualnie_zaznaczona_plytka.x][aktualnie_zaznaczona_plytka.y]->WylaczPodswietlenie(true);
		if (this->aktualnie_podswietlona_plytka.x >= 0) {
			this->plytki[aktualnie_podswietlona_plytka.x][aktualnie_podswietlona_plytka.y]->Zaznacz();
			this->aktualnie_zaznaczona_plytka = this->aktualnie_podswietlona_plytka;
		}
	}

	/**
	 * @brief Funkcja sprawdza czy gracz moze ruszyc sie na dany kafelek (tylko sasiadujace) a przesowa gracza na ten kafelek oraz przeprowadza spotaknie z obiektem (jesli takowy istnieje)
	 * @return true jezeli ruch zostal wykonany
	 * 
	 */
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

	/**
	 * @brief Funkcja obsluguje ruch mapy, generowanie nowych kafelkow na krawedziach oraz losowe generowanie obiektow na tych kafelkach
	 *
	 * @param kierunek Okresla kierunek w ktorym ma przesunac sie mapa, 0 lewo, 1 prawo, 2 gora, 3 dol
	 */
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
	/**
	 * @brief Funkcja zwraca wskaznik na aktualnie zaznaczona plytke
	 * @return Plytka zwraca wskaznik na aktualnie oznaczona plytke
	 */
	Plytka* zwrocAktualnieZaznaczona() {
		return this->plytki[this->aktualnie_zaznaczona_plytka.x][this->aktualnie_zaznaczona_plytka.y];
	}
	/**
	 * @brief Funkcja zwraca dystans_tworzenia
	 * @return zwraca wielkosc mapy
	 */
	int zwrocDystansTworzenia() {
		return this->dystans_tworzenia;
	}
};

