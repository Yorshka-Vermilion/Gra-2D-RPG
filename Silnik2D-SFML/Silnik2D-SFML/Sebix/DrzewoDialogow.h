#pragma once
#include <vector>
#include <fstream>
#include "Dialog.h"

class DrzewoDialogow {
	std::vector<Dialog*> dialogi;
public:
	DrzewoDialogow(bool czyStworzyc = false) {
		if(czyStworzyc==true)stworzDialog();
	}
	~DrzewoDialogow() {
		for (int i = 0; i < dialogi.size(); i++) {
			delete this->dialogi[i];
		}
		dialogi.clear();
	}

	void stworzDialog() {
		this->dialogi.push_back(new Dialog());
	}

	void dodajDialog() {
		std::cout << "Podaj klucz dialogu do dodania okna" << std::endl;
		int klucz = 0;
		std::cin >> klucz;
		while (klucz<0 || klucz>this->dialogi.size()) {
			std::cin >> klucz;
		}
		this->dialogi[klucz]->dodajNoweOkno();
	}

	void usunDialog() {
		std::cout << "Podaj klucz dialogu wykasowania w nim okna" << std::endl;
		int klucz = 0;
		std::cin >> klucz;
		while (klucz<0 || klucz>this->dialogi.size()) {
			std::cin >> klucz;
		}
		this->dialogi[klucz]->usunOkno();
	}

	int przeprowadzDialog(int ist = -1) {
		int klucz = 0;
		if (ist == -1) {
			std::cout << "Podaj klucz dialogu do odczytania" << std::endl;
			std::cin >> klucz;
			while (klucz<0 || klucz>this->dialogi.size()) {
				std::cin >> klucz;
			}
		}
		else klucz = ist;
		if (!this->dialogi[klucz]->dialog.empty()) {
			Wiadomosc* start = this->dialogi[klucz]->dialog[0];
			while (true) {
				std::cout << start->tresc << std::endl;
				if (start->odpowiedzi.empty()) return 0; 
				for (int i = 0; i < start->odpowiedzi.size(); i++) {
					std::cout << i + 1 << " " << start->odpowiedzi[i].tresc << std::endl;
				}
				std::cout << "Wybierz Odpowiedz: " << std::endl;
				int odpowiedz;
				std::cin >> odpowiedz;
				odpowiedz--;
				if (start->odpowiedzi[odpowiedz].wiadomosc == nullptr) {
					return 1;
				}
				start = start->odpowiedzi[odpowiedz].wiadomosc;
			}
		}
		return -1;
	}
};
