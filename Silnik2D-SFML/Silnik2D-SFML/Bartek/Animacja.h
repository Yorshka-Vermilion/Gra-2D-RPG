#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Obiekt.h"

class Animacja : public Obiekt
{
private:
	int x = 0, y = 0, szerokosc, wysokosc, klatki, klatka, wysokoscMAX = 0, szerokoscMAX = 0; 
	float przerwa, dt = 0; 
	/*! A test class */
	bool pionowa;
	
	void zmienKlatke() { /// Zmienia klatke na nastêpn¹, po dotarciu na ostatni¹ klatke wraca do pierwszej.	
		if (dt > przerwa) { // Je¿eli licznik jest wiêkszy ni¿ podana przerwa zmienia sie klatka animacji
			if (pionowa) {
				this->y += wysokosc;
				if (this->y >= wysokoscMAX)this->y = 0;
			}
			else {
				this->x += szerokosc;
				if (this->x >= wysokosc)this->x = 0;
			}
			dt = 0; // Licznik jest resetowany
		}
	}

public:
	Animacja(std::string sciezka, int pozx, int pozy, int szerokosc, int wysokosc, int klatki, float przerwa, bool pionowa = true) : Obiekt(sciezka, sf::Vector2f(pozx, pozy)){
		this->szerokosc = szerokosc;
		this->wysokosc = wysokosc;
		this->klatki = klatki;
		this->klatka = 1;
		this->pionowa = pionowa;
		this->przerwa = przerwa;
		if(pionowa) this->wysokoscMAX = wysokosc * klatki;
		else this->szerokoscMAX = szerokosc * klatki;

		//Sprite
		this->sprajt.setTextureRect(sf::IntRect(this->x, this->y, this->szerokosc, this->wysokosc));
	}

	void animuj(sf::RenderTarget *cel, const float& dtime) { /// Rysuje i zmienia klatke na nastêpn¹.
		cel->draw(this->sprajt);
		this->dt += dtime;
		zmienKlatke();
		this->sprajt.setTextureRect(sf::IntRect(this->x, this->y, this->szerokosc, this->wysokosc));
	}

	void rusz(sf::Vector2f gdzie) { /// Zmienia pozycje sprite'a
		this->sprajt.setPosition(gdzie);
	}

};

