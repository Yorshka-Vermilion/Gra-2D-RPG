#pragma once
#include "../Bartek/Obiekt.h";

/**
	 * @brief Klasa odpowiedzialna za reprezentacje statystyk bohatera
	 *
	 */
class Statystyki{
public:
	/// <summary>
	/// Ilosc sily czarodzieja
	/// </summary>
	int sila = 1;
	/// <summary>
	/// Mnoznik sily bohatera
	/// </summary>
	float mnoznikSila;
	/// <summary>
	/// Ilosc obrazen czarodzieja
	/// </summary>
	int magicDmg = 1;
	/// <summary>
	/// Mnoznik obrazen czarow
	/// </summary>
	float mnoznikDmg;
	/// <summary>
	/// Ilosc punktow inteligencji czarodzieja
	/// </summary>
	int inteligencja = 1;
	/// <summary>
	/// Mnoznik punktow many 
	/// </summary>
	float mnoznikInteligencja;
	/// <summary>
	/// Wartosc zapisujaca ilosc dostepnych do wydania punktow
	/// </summary>
	int dostepnePunkty;
	/**
	 * @brief Konstruktor tworzacy podstaowe wartosci statystyk
	 *
	 * @param dostepnePunkty ilosc dostepnych punktow do wydania
	 * @param mnoznikSila mnoznik definiujacy ilosc dodatkowe HP bohatera za kazdy punkt
	 * @param mnoznikDmg mnoznik definiujacy ilosc dodatkowych obrazen z czarow bohatera
	 * @param mnoznikInteligencja mnoznik definiujacy ilosc dodatkowych punktow many 
	 */
	Statystyki(int dostepnePunkty, float mnoznikSila, float mnoznikDmg, float mnoznikInteligencja){
		this->dostepnePunkty = dostepnePunkty;
		this->mnoznikSila = mnoznikSila;
		this->mnoznikDmg = mnoznikDmg;
		this->mnoznikInteligencja = mnoznikInteligencja;
	}

	/**
	 * @brief Funkcja wyliczajaca dodatkowy bonus punktow zycia z punktow sily
	 *
	 * @param zycie maksymalna ilosc zycie bohatera
	 * @return float zwraca dodatkowa wartosc zycia jaka przysluguje czarodziejowi za poziom
	 */
	float obliczSila(int zycie) {
		//std::cout << zycie * this->mnoznikSila << "obliczSila " << std::endl;
		return zycie * this->mnoznikSila;
	}
	/**
	 * @brief Funkcja wyliczajaca dodatkowy bonus obrazen magicznych z punktow dmg
	 *
	 * @param dmg obecna wartosc obrazen zaklecia
	 * @return float zwraca dodatkowa wartosc obrazen jaka przysluguje czarodziejowi za poziom
	 */
	float obliczDmg(int dmg) {
		return dmg * this->mnoznikDmg;
	}
	/**
	 * @brief Funkcja wyliczajaca dodatkowy bonus punktow many z punktow inteligencji
	 *
	 * @param mana obecna maksymalna wartosc many gracza
	 * @return float zwraca dodatkowa wartosc many jaka przysluguje czarodziejowi za poziom
	 */
	float obliczInteligencja(int mana) {
		return mana * this->mnoznikInteligencja;
	}
	/**
	 * @brief Funkcja zwraca obecna wartosc sily bohatera
	 *
	 * @return int zwraca ilosc punktow dodanych w sile przez bohatera	 
	 */
	int zwrocSila() {
		return this->sila;
	}
	/**
	 * @brief Funkcja zwraca obecna wartosc dmg bohatera
	 *
	 * @return int zwraca ilosc punktow dodanych w dmg przez bohatera
	 */
	int zwrocDmg() {
		return this->magicDmg;
	}
	/**
	 * @brief Funkcja zwraca obecna wartosc inteligencji bohatera
	 *
	 * @return int zwraca ilosc punktow dodanych w inteligencje przez bohatera
	 */
	int zwrocInteligencja() {
		return this->inteligencja;
	}
	/**
	 * @brief Funkcja zwieksza wartosc dostepnych punktow do wydania o jeden
	 *
	 */
	void zwiekszPunkty() {
		this->dostepnePunkty++;
	}
	/**
	 * @brief Funkcja zmniejsza wartosc dostepnych punktow do wydania o jeden
	 *
	 */
	void zmniejszPunkty() {
		this->dostepnePunkty--;
	}
	/**
	 * @brief Funkcja odpowiedzialna za dodanie wolnego punktu w sile
	 * @param ile mozliwe jest ustawienie wartosci punktow ktore chce sie na to wydac
	 */
	void dodajSila(int ile = 1) {
		if(this->dostepnePunkty>0){
			this->sila+=ile;
			//std::cout << sila << "S";
			this->dostepnePunkty--;
		}
	}
	/**
	 * @brief Funkcja odpowiedzialna za dodanie wolnego punktu w dmg
	 * @param ile mozliwe jest ustawienie wartosci punktow ktore chce sie na to wydac
	 */
	void dodajDmg(int ile = 1) {
		if (this->dostepnePunkty > 0) {
			this->magicDmg += ile;
			this->dostepnePunkty--;
		}
	}
	/**
	 * @brief Funkcja odpowiedzialna za dodanie wolnego punktu w inteligencje
	 * @param ile mozliwe jest ustawienie wartosci punktow ktore chce sie na to wydac
	 */
	void dodajInteligencja(int ile = 1) {
		if (this->dostepnePunkty > 0) {
			this->inteligencja += ile;
			//std::cout << inteligencja << "I";
			this->dostepnePunkty--;
		}
	}
	/**
	 * @brief Funkcja odpowiedzialna za zwrocenie dostepnej ilosci punktow
	 * @return int zwraca ilosc dostepnych punktow
	 */
	int zwrocIloscDostepnychPunktow() {
		return this->dostepnePunkty;
	}





};