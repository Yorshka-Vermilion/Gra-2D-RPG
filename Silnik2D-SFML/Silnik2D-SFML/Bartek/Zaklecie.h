#pragma once
#include "Animacja.h"

class Zaklecie
{
	/// Zapisuje w vectorze 'obraz' (czyli kierunki i kolejnosc) lini ktore musza byc narysowane na ekranie aby uaktywnic dane zaklecie
	std::vector<int> obraz_wzorcowy;
	/// Obrazenia zaklecia
	double dmg;
	/// Mana potrzebna do uzycia
	double mana;
	/// Nazwa zaklecia
	std::string nazwa;
	/// Animacja zaklecia
	Animacja* animacja;
public:
	/**
	 * @brief Konstruktor zaklecia
	 *
	 * @param obraz Obraz wzorcowy zaklecia
	 * @param dmg Obrazenia zaklecia
	 * @param mana Mana potrzebna do rzucenia zaklecia
	 * @param nazwa Nazwa zaklecia
	 * @param animacja Wskaznik na animacje zaklecia
	 */
	Zaklecie(std::vector<int> obraz, double dmg, double mana, std::string nazwa, Animacja *animacja) {//Jeszcze jakis wskaznik na animacje czy cos
		this->obraz_wzorcowy = obraz;
		this->dmg = dmg;
		this->mana = mana;
		this->nazwa = nazwa;
		this->animacja = animacja;
		this->animacja->setOriginOnMiddle();
	}
	/**
	 * @brief Funkcja aktualizujaca animacje zaklecia
	 *
	 * @param cel Wskaznik na cel rysowania
	 * @param dtime Delta czasu (timer)
	 * @return true gdy animacja sie zakonczyla
	 * @return false gdy animacja dalej trwa
	 */
	bool update(sf::RenderTarget* cel, const float& dtime) {
		if (!this->animacja->koniec()) {
			this->animacja->animuj(cel, dtime);
			return false;
		}
		else return true;
	}
	/**
	 * @brief Funkcja sprawdzajaca czy podany w argumencie vector obrazu zgadza sie z vectorem obraz_wzorcowy
	 *
	 * @param co Vector obrazu do sprawdzenia
	 * @return true gdy zaklecie zgadza sie z tym znajdujacym sie w zapisanym zbiorze
	 * @return false gdy zaklecie nie znajduje sie w zapisanym zbiorze lub jest nie do rozpoznania
	 */
	bool sprawdz(std::vector<int> co) {
		if (co.size() == this->obraz_wzorcowy.size()) {
			for (size_t i = 0; i < this->obraz_wzorcowy.size(); i++) {
				if (this->obraz_wzorcowy[i] != co[i]) return false;
			}
			return true;
		}
		else return false;
	}
	/**
	 * @brief Funkcja zwracajaca nazwe zaklecia
	 * @return string zwraca nazwe zaklecia
	 */
	std::string getNazwa() {
		return this->nazwa;
	}
	/**
	 * @brief Funkcja resetujaca animacje zaklecia
	 *
	 */
	void zresetuj() {
		this->animacja->zresetuj();
	}
	/**
	 * @brief Funkcja ustawiajaca zaklecia na odpowiedniej pozycji
	 *
	 * @param gdzie Vector2f z pozycja na ktorej ma sie znalezc zaklecie
	 */
	void ustaw(sf::Vector2f gdzie) {
		this->animacja->rusz(gdzie);
	}
	/**
	 * @brief Funkcja zwraca obrazenia zaklecia
	 * @return double zwraca ilosc obrazen zaklecia
	 */
	double getDmg() {
		return this->dmg;
	}
	/**
	 * @brief Funkcja zwraca mane potrzebna do rzucenia zaklecia
	 * @return double zwraca koszt many
	 */
	double getManaCost() {
		return this->mana;
	}

};

