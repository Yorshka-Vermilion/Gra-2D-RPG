#pragma once
#include "Zaklecie.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../Sebix/Funkcje.h"
#include "../Sebix/Point2DArray.h"
#include <cmath>

enum spelle {LEWO,PRAWO,GORA,DOL};

class RzucanieZaklec
{
	std::vector<Zaklecie*> zaklecia;
	std::vector<Point2DArray> linie;
	Point2DArray tmp;
	
public:
	RzucanieZaklec() {
		//Robienie zaklec
		std::vector<int> tm;
		tm.push_back(PRAWO);
		tm.push_back(PRAWO);
		tm.push_back(LEWO);
		this->zaklecia.push_back(new Zaklecie(tm,100,"FIREBALL"));

		tm.clear();
		tm.push_back(GORA);
		tm.push_back(DOL);
		tm.push_back(PRAWO);
		this->zaklecia.push_back(new Zaklecie(tm, 50, "BLYSKAWICA"));
	}

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

	size_t sprawdz(std::vector<int> kierunki) {
		for (size_t i = 0; i < zaklecia.size(); i++) {
			if (this->zaklecia.at(i)->sprawdz(kierunki)) {
				return i;
			}
		} return -1;
	}

	std::string rzucaj() {
		int o = oblicz();
		if (o >= 0) {
			return "Rzucono czar " + this->zaklecia.at(o)->getNazwa();
		}

		return "Nie rzucono czaru";
	}

	void zapiszPoczatek(sf::Vector2f gdzie) {
		this->tmp = Point2DArray();
		this->tmp.add2DPoint(gdzie);
	}

	void zapiszKoniec(sf::Vector2f gdzie) {
		this->tmp.add2DPoint(gdzie);
		this->linie.push_back(tmp);
		this->tmp.clear();
	}

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
	
	void wyczyscLinie() {
		this->linie.clear();
		this->tmp.clear();
	}

};

