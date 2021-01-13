#pragma once
#include "Obiekt.h"
#include "Gracz.h"
#include "Zaklecie.h"
#include "../Sebix/ObiektOtoczenia.h"

class Plytka : public Obiekt
{
	/// Zmienna sluzaca do sprawdzania czy mozna przejsc na plytke
	bool dostepna = true;
	/// Tekstura podswietlenia
	sf::Texture podswietlenie;
	/// Tekstura zaznaczenia
	sf::Texture zaznaczenie;
	/// Flaga sygnalizujaca czy Plytka jest aktualnie zaznaczona
	bool zaznaczona = false;
	/// Wskaznik na zaklecie ktore moze znajdowac sie na plytce
	Zaklecie* zaklecie = nullptr;

public:
	/// Wskaznik na obiekt otorzenia ktory moze znajdowac sie na plytce
	ObiektOtoczenia* otoczenie = nullptr;
	/**
	* @brief Funkcja dodajaca zaklecie na plytke (w celu animacji)
	*
	* @param zaklecie Wskaznik na zaklecie ktore ma byc zanimowane na tej plytce
	*/
	void DodajZaklecie(Zaklecie* zaklecie) {
		this->zaklecie = zaklecie;
		this->zaklecie->zresetuj();
		this->zaklecie->ustaw(sf::Vector2f(this->sprajt.getPosition().x,this->sprajt.getPosition().y));
	}
	/**
	 * @brief Konstruktor plytki
	 *
	 * @param sciezka Sciezka do tekstury plytki
	 * @param sciezka_podswietlenia Sciezka do tekstury podswietlenia plytki
	 * @param pozycja Pozycja plytki
	 */
	Plytka(std::string sciezka, std::string sciezka_podswietlenia, sf::Vector2f pozycja) : Obiekt(sciezka, pozycja) {
		if (!this->podswietlenie.loadFromFile(sciezka_podswietlenia)) {
			std::cout << "Blad ladowania tekstury podswietlenia plytki" << std::endl;
		}

		if (!this->zaznaczenie.loadFromFile("zaznaczenie.png")) {
			std::cout << "Blad ladowania tekstury podswietlenia plytki" << std::endl;
		}

	}
	/**
	 * @brief Dekonstruktor plytki
	 */
	~Plytka() {
		delete(this->otoczenie);
	}
	/**
	 * @brief Funkcja rysujaca plytke na ekranie
	 *
	 * @param cel Wskaznik na cel rysowania
	 */
	void draw(sf::RenderTarget* cel) {
		cel->draw(this->sprajt);
		if(this->otoczenie != nullptr)
			this->otoczenie->draw(cel);
	}
	/**
	 * @brief Funkcja animujaca zaklecie znajdujace sie na plytce
	 *
	 * @param cel Wskaznik na cel rysowania
	 * @param dtime Delta czasu (timer)
	 */
	void animuj(sf::RenderTarget* cel, const float& dtime) {
		if (this->zaklecie != nullptr) {
			if (this->zaklecie->update(cel, dtime)) {
				this->zaklecie = nullptr;
			};
		}
	}
	/**
	 * @brief Funkcja aktualizujaca stan plytki
	 * @return double zwraca wartosc punktow doswiadczenia ktore ma uzyskac gracz
	 */
	double update() {
		if (this->otoczenie != nullptr) {
			if (this->otoczenie->checkZycie() == true){
				double returnExpValue = this->otoczenie->returnExp();
				this->ZmienDostepnosc(true);
			    delete(this->otoczenie);
				this->otoczenie = nullptr;
				return returnExpValue;
			}
		}
		
		return 0;
	}
	/**
	 * @brief Funkcja przypisujaca gracza do plytki
	 *
	 * @param obiekt Wskaznik na gracza do przypisania
	 */
	void PrzypiszGracza(Gracz* gracz) {
		gracz->rusz(sf::Vector2f(this->sprajt.getPosition().x, this->sprajt.getPosition().y - this->tekstura.getSize().y / 4));
	}
	/**
	 * @brief Funkcja przypisujaca obiekt do plytki
	 *
	 * @param obiekt Wskaznik na obiekt do przypisania
	 */
	void PrzypiszObiekt(ObiektOtoczenia* obiekt) {
		this->otoczenie = obiekt;
		this->otoczenie->przestaw(sf::Vector2f(this->sprajt.getPosition().x, this->sprajt.getPosition().y - this->tekstura.getSize().y / 4));
		if(this->otoczenie->zwrocFlage() == 1) this->ZmienDostepnosc(false);
	}

	/**
	 * @brief Funkcja zmieniajaca dostepnasc plytki
	 *
	 * @param jak Typ logiczny wskazujacy na jaka wartosc ma byc zmieniona dostepnosc plytki
	 */
	void ZmienDostepnosc(bool jak) {
		this->dostepna = jak;
	}
	/**
	 * @brief Funkcja podswietlajaca plytke (ustawia teksture podswietlenia)
	 *
	 */
	void Podswietl() {
		if (!this->zaznaczona)this->sprajt.setTexture(this->podswietlenie);
	}
	/**
	 * @brief Funkcja wylaczajaca podswietlenie (wraca do domyslnej tekstury)
	 *
	 */
	void WylaczPodswietlenie(bool force = false) {
		if (force || !this->zaznaczona) {
			this->sprajt.setTexture(this->tekstura);
			this->zaznaczona = false;
		}
	}
	/**
	 * @brief Funkcja zaznaczajaca plytke (ustawia teksture zaznaczenia)
	 *
	 */
	void Zaznacz() {
		if (!zaznaczona) {
			this->sprajt.setTexture(this->zaznaczenie);
			this->zaznaczona = true;
		}
		else WylaczPodswietlenie(true);

	}
	/**
	 * @brief Funkcja zwraca ObiektOtoczenia ktory znajduje sie na plytce, jesli nie znajduje sie zaden zwraca nullptr
	 * @return ObiektOtoczenia zwraca obiekt znajdujacy sie w wybranym miejscu
	 * 
	 */
	ObiektOtoczenia* zwrocObiekt() {
		if(this->otoczenie != nullptr)
			return this->otoczenie;
	}
	/**
	 * @brief Funkcja zwraca typ logiczny wskazujacy na dostepnasc plytki
	 * @return true jezeli plytka jest dostepna
	 * @return false jezeli plytka jest niedostêpna 
	 */
	bool zwrocDostepnosc() {
		return this->dostepna;
	}
	/**
	 * @brief Funkcja aktualizuje pozycje obiektu znajdujacego sie na plytce (przy przesuwaniu, razem z plytka przesuwa sie obiekt)
	 *
	 */
	void aktualizujObiekt() {
		if(this->otoczenie)
			this->otoczenie->przestaw(sf::Vector2f(this->sprajt.getPosition().x, this->sprajt.getPosition().y - this->tekstura.getSize().y / 4));
	}

};