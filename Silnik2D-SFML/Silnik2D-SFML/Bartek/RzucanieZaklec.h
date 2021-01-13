#pragma once
#include "Zaklecie.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Sebix/Funkcje.h"
#include "../Sebix/Point2DArray.h"
#include "Gracz.h"
#include "Plytka.h"
#include <cmath>

/// Kierunki rzucania czarow
enum spelle {LEWO,PRAWO,GORA,DOL};
/**
	 * @brief Klasa obslugujaca rzucanie zaklec
	 *
	 */
class RzucanieZaklec
{
	/// Vector przechowujacy wszystkie dostepne w grze zaklecia
	std::vector<Zaklecie*> zaklecia;
	/// Vector przechowujacy linie rysujace sie na ekranie podczas rzucania czaru
	std::vector<Point2DArray> linie;
	/// Tymczasowa klasa Point2DArray ktora przechowuje pojedyncza linie
	Point2DArray tmp;
	/// Wskaznik na gracza
	Gracz* gracz;
	
public:
	/**
	 * @brief Konstruktor rzucania zaklec
	 *
	 * @param gracz Wskaznik na gracza
	 */
	RzucanieZaklec(Gracz* gracz) {
		//Robienie zaklec
		this->gracz = gracz;
		std::vector<int> tm;
		tm.push_back(PRAWO);
		tm.push_back(PRAWO);
		tm.push_back(LEWO);
		this->zaklecia.push_back(new Zaklecie(tm,100,100,"FIREBALL", new Animacja("fireball.png", 0, 0, 148, 140, 8, 0.05, true, false)));

		tm.clear();
		tm.push_back(GORA);
		tm.push_back(DOL);
		tm.push_back(PRAWO);
		this->zaklecia.push_back(new Zaklecie(tm, 50,25, "BLYSKAWICA", new Animacja("lightning.png", 0, 0, 160, 240, 5, 0.1, true, false)));
	}
	/**
	 * @brief Funkcja oblicza kierunei narysowanych lini oraz zwraca index zaklecia jesli kierunki lini pokryly sie z jakims zakleciem w vectorze zaklecia
	 * @return int numer zaklecia ktore zgadza sie ze wskazanymi znakami
	 * @return -1 gdy narysowane linie nie odpowiadaja zadnemu z czarow
	 */
	int oblicz() {
		std::vector<int> kierunki;
		for (size_t i = 0; i < this->linie.size(); i++) {
			int X = this->linie.at(i).p2d[0].getX() - this->linie.at(i).p2d[1].getX();
			int Y = this->linie.at(i).p2d[0].getY() - this->linie.at(i).p2d[1].getY();

			if (std::abs(X) > std::abs(Y)) {
				if (X < 0) kierunki.push_back(PRAWO);
				else kierunki.push_back(LEWO);
			}
			else {
				if (Y < 0) kierunki.push_back(DOL);
				else kierunki.push_back(GORA);
			}
		}
		if (kierunki.size() > 0) {
			return sprawdz(kierunki);
		}
		else return -1;
	}
	/**
	 * @brief Funkcja sprawdza czy jakiekolwiek zaklecie i jego kierunki odpowiadaja vectorowi kierunkow podanemu w argumencie
	 *
	 * @param kierunki Vector kierunkow ktore odpowiadaja narysowanym linia
	 * @return i zwraca numer wskazanego zaklecia ze zbioru
	 * @return -1 gdy odpowiadajace zaklecie nie znajduje wie w zbiorze
	 */
	size_t sprawdz(std::vector<int> kierunki) {
		for (size_t i = 0; i < zaklecia.size(); i++) {
			if (this->zaklecia.at(i)->sprawdz(kierunki)) {
				return i;
			}
		} return -1;
	}
	/**
	 * @brief Funkcja obslugujaca rzucanie zaklec, zwraca odpowiedni komunikat w postaci string'a
	 *
	 * @param plytka Wskaznik na plytke na ktorej ma byc rzucony czar
	 * @return string zwraca komunikat zaleznie od efektu rzuconego czaru
	 */
	std::string rzucaj(Plytka* plytka) {
		int o = oblicz();
		if (o >= 0 && plytka->zwrocObiekt() != nullptr) {
			if (this->gracz->mana >= this->zaklecia.at(o)->getManaCost()){
				this->gracz->odejmijMane(this->zaklecia.at(o)->getManaCost());
				zadajObrazenia(plytka,this->zaklecia.at(o)->getDmg());
				plytka->DodajZaklecie(this->zaklecia.at(o));
				return "Rzucono czar " + this->zaklecia.at(o)->getNazwa();
			}
			return "Zbyt mala ilosc many";
		}
		return "Nie rzucono czaru";
	}
	/**
	 * @brief Funkcja zadaje obrazenia obiektowi znajdujacemu sie na plytce
	 *
	 * @param plytka Wskaznik na plytke na ktorej stoi obiekt
	 * @param dmg Ilosc obrazen do zadania
	 */
	void zadajObrazenia(Plytka* plytka, int dmg) {
		plytka->zwrocObiekt()->dealDmg(dmg + this->gracz->statystyki->obliczDmg(dmg));
	}
	/**
	 * @brief Funkcja zapisujaca poczatek lini rysowanej w celu rzucania zaklecia
	 *
	 * @param gdzie Pozycja piksela na ktorym zaczeto rysowanie lini
	 */
	void zapiszPoczatek(sf::Vector2f gdzie) {
		this->tmp = Point2DArray();
		this->tmp.add2DPoint(gdzie);
	}
	/**
	 * @brief Funkcja zapisujaca koniec lini rysowanej w celu rzucania zaklecia
	 *
	 * @param gdzie Pozycja piksela na ktorym skonczono rysowanie lini
	 */
	void zapiszKoniec(sf::Vector2f gdzie) {
		this->tmp.add2DPoint(gdzie);
		this->linie.push_back(tmp);
		this->tmp.clear();
	}
	/**
	 * @brief Funkcja zapisujaca rysujaca linie rzucania zaklec
	 *
	 * @param target Cel rysowania
	 * @param myszka Aktualna pozycja myszy w celu rysowania z punktu poczatkowego do myszy
	 */
	void draw(sf::RenderTarget* target, sf::Vector2f myszka) {
		size_t rozmiar = this->linie.size();
		for (size_t i = 0; i < rozmiar; i++) {
			draw2DLine(this->linie[i], target);
		}
		if (!this->tmp.p2d.empty()) {
			if (this->tmp.p2d.size() == 1) {
				draw2DLine(this->tmp.p2d[0], Point2D(myszka), target);
			}
		}
		
	}
	/**
	 * @brief Funkcja czyszczaca linie po rzuceniu czaru
	 *
	 */
	void wyczyscLinie() {
		this->linie.clear();
		this->tmp.clear();
	}
};

