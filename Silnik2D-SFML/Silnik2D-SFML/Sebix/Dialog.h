#pragma once
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <string>
constexpr auto MAX = 5;

struct Wiadomosc;
/**
	 * @brief Struktura odpowiadajaca tworzenie postaci w dialogcach
	 */
struct Opcje {
	/// <summary>
	/// Tresc opcji
	/// </summary>
	std::string tresc;
	/// <summary>
	/// Kolejna wiadomosc w kolejce
	/// </summary>
	Wiadomosc* wiadomosc;

	/**
	 * @brief Konstruktor opcji
	 *
	 * @param tresc Tresc wiadomosci
	 * @param wiadomosc Odpowiedzialna za przydzielenie wiadomosci do opcji
	 */
	Opcje(std::string tresc, Wiadomosc* wiadomosc) {
		this->tresc = tresc;
		this->wiadomosc = wiadomosc;
	}
	/**
	 * @brief Pozwala edytowac tresc odpowiedzi
	 *
	 * @param tresc Nowa tresc dla odpowiedzi
	 */
	void edytujTrescOdpowiedzi(std::string tresc) {
		this->tresc = tresc;
	}
	/**
	 * @brief Pozwala edytowaæ pelna wiadomosc w dialogu
	 *
	 * @param wiadomosc Wskaznik na wiadomosc ktora ma zostac przypisana jako nowa wiadomosc docelowa
	 */
	void edytujOknoDocelowe(Wiadomosc* wiadomosc) {
		this->wiadomosc = wiadomosc;
	}
};

/**
	 * @brief Reprezentuje wiadomosc w dialogach
	 */
struct Wiadomosc {
	/// <summary>
	/// Okresla tresc wiadomosci
	/// </summary>
	std::string tresc;
	/// <summary>
	/// Wektor odpowiedzi okreslajacy konsekwencje decyzji
	/// </summary>
	std::vector <Opcje> odpowiedzi;

	/**
	 * @brief Konstruktor domyslny pustej wiadomosci
	 *
	 */
	Wiadomosc(){}
	/**
	 * @brief Konstruktor tworzacy wiadomosc
	 *
	 * @param tresc Odpowiada za tresc wiadomosci
	 */
	Wiadomosc(std::string tresc) {
		this->tresc = tresc;
	}
	/**
	 * @brief Funkcja pozwala edytowac tresc wiadomosci
	 *
	 * @param tresc okresla nowa tresc odpowiedzi
	 */
	void edytujTrescWiadomosci(std::string tresc) {
		this->tresc = tresc;
	}
	/**
	 * @brief Funkcja pozwala na dodanie nowej odpowiedzi do wiadomosci
	 *
	 * @param inputOdpowiedzi tresc odpowiedzi
	 * @param wiadomosc Wskaznik na wiadomosci do ktorej ma sie odnosic odpowiedz
	 */
	void dodajOpcje(std::string inputOdpowiedzi, Wiadomosc *wiadomosc) {
		this->odpowiedzi.push_back(Opcje(inputOdpowiedzi, wiadomosc));
	}
};

/**
	 * @brief Klasa reprezentujaca dialog
	 *
	 */
class Dialog {
public:
	/// <summary>
	/// Wektor wskaznikow na odpowiedzi okreslajacy dialog
	/// </summary>
	std::vector<Wiadomosc*> dialog;
	/**
	 * @brief Konstruktor domyslny tworzacy nowy dialog
	 *
	 */
	Dialog() {
		stworzGalaz();
	}
	/**
	 * @brief Dekonstruktor dialogow
	 *
	 */
	~Dialog() {
		usunGalaz();
	}

	/**
	 * @brief Odswiezenie stanu gry
	 *
	 * @param dtime Delta czasu (timer)
	 * @return int zwraca wielkosc dialogu
	 */
	int zwrocWielkoscGalezi() {
		return this->dialog.size();
	}
	/**
	 * @brief Funkcja odpowiada za stworzenie pelnego dialogu poprzez konsole
	 *
	 */
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

	/**
	 * @brief Funkcja pozwala na dodanie nowego dialogu
	 *
	 */
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

	/**
	 * @brief Funkcja odpowiada za usuniecie dialogu
	 *
	 */
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
	/**
	 * @brief Funkcja odpowiada za usuniecie wszystkich dialogow
	 *
	 */
	void usunGalaz() {
		for (int i = 0; i < dialog.size(); i++) {
			delete this->dialog[i];
		}
		dialog.clear();
	}
};