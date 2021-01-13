#pragma once
#include "../Bartek/Obiekt.h";
#include "../Bartek/Gracz.h"

/**
	 * @brief Klasa odpowiedzialna za reprezentacje statystyk w trakcie rozgrywki
	 */
class StatInGame{
	/// <summary>
	/// Przycisk reprezentujacy tlo menu rozdawania statystyk+
	/// </summary>
	Obiekt* back;
	/// <summary>
	/// Przycisk reprezentujacy opcje dodania punktow w sile
	/// </summary>
	Obiekt* buttonSila;
	/// <summary>
	/// Przycisk reprezentujacy opcje dodania punktow w dmg
	/// </summary>
	Obiekt* buttonDmg;
	/// <summary>
	/// Przycisk reprezentujacy opcje dodania punktow w inteligencje
	/// </summary>
	Obiekt* buttonInteligencja;
	/// <summary>
	/// Czcionka wyswietlajaca sie w menu statystyk
	/// </summary>
	sf::Font czcionka;
public:
	/// <summary>
	/// Reprezentacja tekstowana w oknie punktow sily
	/// </summary>
	sf::Text sila;
	/// <summary>
	/// Reprezentacja tekstowana w oknie punktow dmg
	/// </summary>
	sf::Text dmg;
	/// <summary>
	/// Reprezentacja tekstowana w oknie punktow inteligencji
	/// </summary>
	sf::Text inteligencja;
	/**
	 * @brief Konstruktor budujacy statystyki w trakcie rozgrywki
	 *
	 * @param sila ilosc punktow ktore posiada bohater w sile
	 * @param dmg ilosc punktow ktore posiada bohater w dmg
	 * @param inteligencja ilosc punktow ktore posiada bohater w inteligencji
	 */
	StatInGame(int sila, int dmg, int inteligencja){
		this->makeInGameStat(sila,dmg,inteligencja);
	}
		/**
	 * @brief Funkcja odpowiedzialna za zbudowanie menu statystyk
	 *
	 * @param sila ilosc punktow ktore posiada bohater w sile
	 * @param dmg ilosc punktow ktore posiada bohater w dmg
	 * @param inteligencja ilosc punktow ktore posiada bohater w inteligencji
	 */
	void makeInGameStat(int sila, int dmg, int inteligencja) {
		this->back = new Obiekt("statbackborad.png", sf::Vector2f(50, 50));
		this->back->przeskaluj(sf::Vector2f(3, 3));
		this->back->sprajt.setColor(sf::Color(255, 255, 255, 75));
		this->sila = this->zrobTekst("Bandwidth 8x8.ttf", sf::Vector2f(this->back->sprajt.getPosition().x + this->back->sprajt.getTexture()->getSize().x+25, this->back->sprajt.getPosition().y + (this->back->sprajt.getTexture()->getSize().y * this->back->sprajt.getScale().y/8)), "Sila: ", sila);
		this->buttonSila = new Obiekt("plus.png", sf::Vector2f(0, 0));
		this->buttonSila->przeskaluj(sf::Vector2f(1.5, 1.5));
		this->buttonSila->sprajt.setColor(sf::Color(255, 255, 255, 100));
		this->buttonSila->setOriginOnMiddle();
		this->buttonSila->przestaw(sf::Vector2f(this->sila.getPosition().x, this->sila.getPosition().y + 40));

		this->dmg = this->zrobTekst("Bandwidth 8x8.ttf", sf::Vector2f(this->back->sprajt.getPosition().x + this->back->sprajt.getTexture()->getSize().x + 33,this->buttonSila->sprajt.getPosition().y+80) , "Magic Damage: ", dmg);
		this->buttonDmg = new Obiekt("plus.png", sf::Vector2f(0, 0));
		this->buttonDmg->przeskaluj(sf::Vector2f(1.5, 1.5));
		this->buttonDmg->sprajt.setColor(sf::Color(255, 255, 255, 100));
		this->buttonDmg->setOriginOnMiddle();
		this->buttonDmg->przestaw(sf::Vector2f(this->sila.getPosition().x, this->dmg.getPosition().y + 40));
		
		this->inteligencja = this->zrobTekst("Bandwidth 8x8.ttf", sf::Vector2f(this->back->sprajt.getPosition().x + this->back->sprajt.getTexture()->getSize().x + 30, this->buttonDmg->sprajt.getPosition().y+80), "Inteligencja: ", inteligencja);
		this->buttonInteligencja = new Obiekt("plus.png", sf::Vector2f(0, 0));
		this->buttonInteligencja->przeskaluj(sf::Vector2f(1.5, 1.5));
		this->buttonInteligencja->sprajt.setColor(sf::Color(255, 255, 255, 100));
		this->buttonInteligencja->setOriginOnMiddle();
		this->buttonInteligencja->przestaw(sf::Vector2f(this->sila.getPosition().x, this->inteligencja.getPosition().y + 40));

	}

	/**
 * @brief Funkcja tworzaca reprezentacje graficzna w formie tekstu
 *
 * @param sciezka odpowiada za znajdowanie pliku reprezentujacego statystyki
 * @param pozycja odpowaida za pozycje w ktorej maja sie znajdowac statystyki
 * @param tresc nazwa wybranej statystyki
 * @param wartosc wartosc wybranej statystyki\
 * @return Text zwraca gotowy obraz reprezentujacy statystyke
 */
	sf::Text zrobTekst(std::string sciezka, sf::Vector2f pozycja, std::string tresc, int wartosc) {
		if (!this->czcionka.loadFromFile(sciezka)) {
			std::cout << "Nie udalo sie zaladowac czcionki" << std::endl;
		}
		sf::Text text;
		text.setFont(czcionka);
		text.setFillColor(sf::Color(255,255,255,125));
		text.setOutlineColor(sf::Color::Black);
		text.setCharacterSize(80);
		text.setOutlineThickness(4);
		text.scale(0.15, 0.15);
		text.setString(std::string(tresc).append(std::to_string(wartosc)));
		sf::FloatRect center = text.getLocalBounds();
		text.setOrigin(center.left + center.width / 2, center.top + center.height / 2);
		text.setPosition(pozycja);
		return text;
	}
/**
* @brief Funkcja odpowiedzialna za zwrocenie wskaznika na tylnia czesc menu
*
* @return Obiekt zwraca wskaznik na tlo statystyk
*/
	Obiekt* zwrocOkno() {
		return this->back;
	}
	/**
	* @brief Funkcja odpowiedzialna za zwrocenie wskaznika na przycisk sily z menu
	*
	* @return Obiekt zwraca wskaznik na przycisk sily
	*/
	Obiekt* zwrocPrzyciskSila() {
		return this->buttonSila;
	}
	/**
	* @brief Funkcja odpowiedzialna za zwrocenie wskaznika na przycisk dmg  z menu
	*
	* @return Obiekt zwraca wskaznik na przycisk dmg
	*/
	Obiekt* zwrocPrzyciskDmg() {
		return this->buttonDmg;
	}
	/**
	* @brief Funkcja odpowiedzialna za zwrocenie wskaznika na przycisk inteligencji z menu
	*
	* @return Obiekt zwraca wskaznik na przycisk inteligencji
	*/
	Obiekt* zwrocPrzyciskInteligencja() {
		return this->buttonInteligencja;
	}
	/**
* @brief Funkcja odpowiedzialna za rysowanie menu na ekranie w trakcie gry
*
* @param target okno w ktorym ma byc przedstawiane menu
*/
	void draw(sf::RenderTarget* target) {
		this->back->draw(target);
		this->buttonSila->draw(target);
		this->buttonDmg->draw(target);
		this->buttonInteligencja->draw(target);
		target->draw(this->sila);
		target->draw(this->dmg);
		target->draw(this->inteligencja);
	}
/**
* @brief Funkcja odpowiedzialna za wyswietlanie podgladu statystyk
*
* @param target okno w ktorym ma byc przedstawiane menu
*/
	void drawStat(sf::RenderTarget* target) {
		target->draw(this->sila);
		target->draw(this->dmg);
		target->draw(this->inteligencja);
	}
	/**
* @brief Funkcja odpowiedzialna za aktualizacje wartosci sily w menu statystyk
*
*
* @param tresc tresc statystyki
* @param wartosc wartosc punktow jaka ma sie wyswietlac
*/
	void aktualizujSila(std::string tresc, int wartosc) {
		this->sila.setString(std::string(tresc).append(std::to_string(wartosc)));
	}
	/**
* @brief Funkcja odpowiedzialna za aktualizacje wartosci dmg w menu statystyk
*
* @param tresc tresc statystyki
* @param wartosc wartosc punktow jaka ma sie wyswietlac
*/
	void aktualizujDmg(std::string tresc, int wartosc) {
		this->dmg.setString(std::string(tresc).append(std::to_string(wartosc)));
	}
	/**
* @brief Funkcja odpowiedzialna za aktualizacje wartosci inteligencji w menu statystyk
*
* @param tresc tresc statystyki
* @param wartosc wartosc punktow jaka ma sie wyswietlac
*/
	void aktualizujInteligencja(std::string tresc, int wartosc) {
		this->inteligencja.setString(std::string(tresc).append(std::to_string(wartosc)));
	}



};