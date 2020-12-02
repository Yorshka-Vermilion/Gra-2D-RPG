#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Plytka.h"

class Mapa
{
	std::vector<std::vector<Plytka*>> plytki;
	float szerokosc;
	float wysokosc;
	float przerwa_pomiedzy;
	sf::Vector2u pozycja_poczatkowa;

public: 
	Mapa(float przerwa_pomiedzy, sf::Vector2u pozycja_poczatkowa) {
		this->przerwa_pomiedzy = przerwa_pomiedzy;
		for (size_t i = 0; i < 5; i++) {
			this->plytki.push_back(std::vector<Plytka*>());
			for (size_t j = 0; j < 5; j++) {
				this->plytki[i].push_back(new Plytka("plytka2.png", sf::Vector2f(0, 0)));
				//this->plytki[i].insert(this->plytki[i].begin(), new Plytka("kupa.png", sf::Vector2f(0, 0)));
			}
		}

		//Ustawia poczatkowa pozycje na srodku ekranu
		this->pozycja_poczatkowa = pozycja_poczatkowa;
		this->pozycja_poczatkowa.x = this->pozycja_poczatkowa.x / 2;
		this->pozycja_poczatkowa.y = this->pozycja_poczatkowa.y / 2;

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
					((wysokosc/2) * (j + 1 + i*2)) - ((wysokosc/2)*i) + this->pozycja_poczatkowa.y - (wysokosc*(plytki.size()-2))));
				j++;
			}
			i++;
		}
	}

	void PrzypiszBohatera() { // Przypisuje bohatera do plytki
		//this->plytki[this->plytki.size() / 2][this->plytki[this->plytki.size() / 2].size() / 2]->PrzypiszGracza(JAKIS WSKAZNIK NA GRACZA);
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
				this->plytki[i][j]->rysuj(cel);
				j++;
			}
			i++;
		}
	}

	void Przesun(int kierunek) { // 0 lewo, 1 prawo, 2 gora, 3 dol
		if (!this->plytki.empty()) {
			size_t v1s = this->plytki.size();
			size_t v2s = this->plytki[0].size();
			if (kierunek == 0) {
				this->plytki.pop_back();
				this->plytki.insert(this->plytki.begin(), std::vector<Plytka*>());
				for (size_t j = 0; j < v2s; j++) {
					this->plytki[0].push_back(new Plytka("plytka3.png", sf::Vector2f(0, 0)));
				}
			}
			else if (kierunek == 1) {
				this->plytki.erase(this->plytki.begin());
				this->plytki.push_back(std::vector<Plytka*>());
				for (size_t j = 0; j < v2s; j++) {
					this->plytki[v1s-1].push_back(new Plytka("plytka3.png", sf::Vector2f(0, 0)));
				}
			}
			else if (kierunek == 2) {
				for (size_t i = 0; i < v1s; i++) {
					this->plytki[i].pop_back();
					this->plytki[i].insert(this->plytki[i].begin(), new Plytka("plytka3.png", sf::Vector2f(0, 0)));
				}
				
			}
			else if (kierunek == 3) {
				for (size_t i = 0; i < v1s; i++) {
					this->plytki[i].erase(this->plytki[i].begin());
					this->plytki[i].push_back(new Plytka("plytka3.png", sf::Vector2f(0, 0)));
				}
			}
			UstawPlytki();
		}
		
	}
};

