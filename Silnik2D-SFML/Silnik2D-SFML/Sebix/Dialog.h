#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
constexpr auto MAX = 5;

struct Wiadomosc;

struct Opcje {
	std::string tresc;
	Wiadomosc* wiadomosc;

	Opcje(std::string tresc, Wiadomosc* wiadomosc) {
		this->tresc = tresc;
		this->wiadomosc = wiadomosc;
	}

	void edytujTrescOdpowiedzi(std::string tresc) {
		this->tresc = tresc;
	}

	void edytujOknoDocelowe(Wiadomosc* wiadomosc) {
		this->wiadomosc = wiadomosc;
	}
};

struct Wiadomosc {
	std::string tresc;
	std::vector <Opcje> odpowiedzi;

	Wiadomosc(){}
	Wiadomosc(std::string tresc) {
		this->tresc = tresc;
	}

	void edytujTrescWiadomosci(std::string tresc) {
		this->tresc = tresc;
	}

	void dodajOpcje(std::string inputOdpowiedzi, Wiadomosc *wiadomosc) {
		this->odpowiedzi.push_back(Opcje(inputOdpowiedzi, wiadomosc));
	}
};

class Dialog {
public:
	std::vector<Wiadomosc*> dialog;
	Dialog() {
		stworzGalaz();
	}
	~Dialog() {
		usunGalaz();
	}

	int zwrocWielkoscGalezi() {
		return this->dialog.size();
	}

	void stworzGalaz() {
		int ilosc = 0;
		Wiadomosc* rozmowa[MAX];
		std::cout << "Podaj wielkosc drzewa dialogowego" << std::endl;
		std::cin >> ilosc;
		while (ilosc > MAX || ilosc <= 0) {
			std::cout << "Podaj prawidlowa liczbe okien dialogowych, nie wieksza niz " << MAX << std::endl;
			std::cin >> ilosc;
		}
		for (int i = 0; i < ilosc; i++) {
			rozmowa[i] = new Wiadomosc;
		}
		std::cin.ignore();
		for (int i = 0; i < ilosc; i++) {
			std::cout << "Podaj tresc wiadomosci NPC dla okna " << i+1 << std::endl;
			std::string input;
			std::getline(std::cin, input);
			rozmowa[i]->edytujTrescWiadomosci(input);

			std::cout << "Podaj ilosc odpowiedzi" << std::endl;
			int iloscOdpowiedzi = 0;
			std::cin >> iloscOdpowiedzi;
			for (int j = 0; j < iloscOdpowiedzi; j++) {
				std::cin.ignore();
				std::cout << "Podaj tresc wiadomosci odpowiedzi numer " << j+1 << " dla okna " << i+1<< std::endl;
				std::string inputOdpowiedzi;
				std::getline(std::cin, inputOdpowiedzi);
				std::cout << "Podaj numer okna dialogowego, ktore ma byc skutkiem odpowiedzi numer "<<j+1 << std::endl;
				int numerOdpowiedzi = 0;
				std::cin >> numerOdpowiedzi;
				numerOdpowiedzi--;
				if (numerOdpowiedzi >= ilosc || numerOdpowiedzi < 0) {
					rozmowa[i]->dodajOpcje(inputOdpowiedzi, nullptr);
				}
				else {
					rozmowa[i]->dodajOpcje(inputOdpowiedzi, rozmowa[numerOdpowiedzi]);
				}
			}
			this->dialog.push_back(rozmowa[i]);
			std::cin.ignore();
		}
	}

	void dodajNoweOkno() {
		Wiadomosc* nowy = new Wiadomosc;
		int klucz = 0;
		std::string input;
		std::cout << "Podaj klucz okna do polaczenia z nowym oknem " << std::endl;
		std::cin >> klucz;
		std::cin.ignore();
		std::cout << "Podaj tresc odpowiedzi okna" << std::endl;
		std::getline(std::cin, input);
		this->dialog[klucz]->dodajOpcje(input,nowy);
		std::cout << "Podaj tresc wiadomosci NPC dla nowego okna " << std::endl;
		std::getline(std::cin, input);
		nowy->edytujTrescWiadomosci(input);
		std::cout << "Podaj ilosc odpowiedzi" << std::endl;
		int iloscOdpowiedzi = 0;
		std::cin >> iloscOdpowiedzi;
		for (int j = 0; j < iloscOdpowiedzi; j++) {
			std::cin.ignore();
			std::cout << "Podaj tresc wiadomosci odpowiedzi numer " << j + 1 << " dla nowego okna " << std::endl;
			std::string inputOdpowiedzi;
			std::getline(std::cin, inputOdpowiedzi);
			std::cout << "Podaj numer okna dialogowego, ktore ma byc skutkiem odpowiedzi numer " << j + 1 << std::endl;
			int numerOdpowiedzi = 0;
			std::cin >> numerOdpowiedzi;
			numerOdpowiedzi--;
			if (numerOdpowiedzi >= this->zwrocWielkoscGalezi() || numerOdpowiedzi < 0) {
				nowy->dodajOpcje(inputOdpowiedzi, nullptr);
			}
			else {
				nowy->dodajOpcje(inputOdpowiedzi, this->dialog[numerOdpowiedzi]);
			}
		}
		this->dialog.push_back(nowy);
	}

	void usunOkno() {
		int klucz = 0;
		std::cout << "Podaj klucz okna do usuniêcia z dialogu" << std::endl;
		std::cin >> klucz;
		while (klucz<0 || klucz>this->dialog.size()) {
			std::cin >> klucz;
		}
		for (int i = 0; i < this->dialog.size(); i++) {
			for (int j = 0; j < this->dialog[i]->odpowiedzi.size(); j++) {
				if (this->dialog[i]->odpowiedzi[j].wiadomosc == this->dialog[klucz]) {
					this->dialog[i]->odpowiedzi[j].wiadomosc == nullptr;
					this->dialog[i]->odpowiedzi.erase(this->dialog[i]->odpowiedzi.begin() + klucz);
				}
			}
		}
		this->dialog.erase(this->dialog.begin() + klucz);
		std::cout << this->dialog.size() << std::endl;
	}

	void usunGalaz() {
		for (int i = 0; i < dialog.size(); i++) {
			delete this->dialog[i];
		}
		dialog.clear();
	}
};