#pragma once
#include "../Bartek/Obiekt.h";

class Statystyki{
public:

	int sila = 1;
	float mnoznikSila;
	int magicDmg = 1;
	float mnoznikDmg;
	int inteligencja = 1;
	float mnoznikInteligencja;
	int dostepnePunkty;
	Statystyki(int dostepnePunkty, float mnoznikSila, float mnoznikDmg, float mnoznikInteligencja){
		this->dostepnePunkty = dostepnePunkty;
		this->mnoznikSila = mnoznikSila;
		this->mnoznikDmg = mnoznikDmg;
		this->mnoznikInteligencja = mnoznikInteligencja;
	}

	float obliczSila(int zycie) {
		//std::cout << zycie * this->mnoznikSila << "obliczSila " << std::endl;
		return zycie * this->mnoznikSila;
	}

	float obliczDmg(int dmg) {
		return dmg * this->mnoznikDmg;
	}

	float obliczInteligencja(int mana) {
		//std::cout << mana * this->mnoznikInteligencja << "obliczInt " << std::endl;
		return mana * this->mnoznikInteligencja;
	}

	int zwrocSila() {
		return this->sila;
	}

	int zwrocDmg() {
		return this->magicDmg;
	}

	int zwrocInteligencja() {
		return this->inteligencja;
	}

	void zwiekszPunkty() {
		this->dostepnePunkty++;
	}

	void zmniejszPunkty() {
		this->dostepnePunkty--;
	}
	
	void dodajSila(int ile = 1) {
		if(this->dostepnePunkty>0){
			this->sila+=ile;
			//std::cout << sila << "S";
			this->dostepnePunkty--;
		}
	}

	void dodajDmg(int ile = 1) {
		if (this->dostepnePunkty > 0) {
			this->magicDmg += ile;
			this->dostepnePunkty--;
		}
	}

	void dodajInteligencja(int ile = 1) {
		if (this->dostepnePunkty > 0) {
			this->inteligencja += ile;
			//std::cout << inteligencja << "I";
			this->dostepnePunkty--;
		}
	}

	int zwrocIloscDostepnychPunktow() {
		return this->dostepnePunkty;
	}





};