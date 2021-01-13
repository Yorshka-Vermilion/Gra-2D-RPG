#pragma once
#include "../Bartek/Obiekt.h";

	/**
	 * @brief Klasa odpowiada za reprezentacje graficzna zdrowia bohatera
	 *
	 */
class Zycie : public Obiekt {
	/// <summary>
	/// Wartosc okreslajaca srednice okregu
	/// </summary>
	float diameter;
	/// <summary>
	/// Pozycja zdrowia bohatera
	/// </summary>
	sf::Vector2f hpPos;
	/// <summary>
	/// Obiekt reprezentujacy kule zdrowia bohatera
	/// </summary>
	sf::CircleShape hpCircle;
public:
	/**
	 * @brief Konstruktor odpowiedzialny za zbudowanie zycia
	 *
	 * @param sciezka odpowiada za znajdowanie sie pliku reprezentujacego zdrowie
	 * @param pozycja odpowaida za pozycje w ktorej ma sie znajdowac zdrowie
	 */
	Zycie(std::string sciezka, sf::Vector2f pozycja) : Obiekt(sciezka, pozycja) {
		this->diameter = 100;
		this->hpPos = sf::Vector2f(pozycja.x-this->diameter /2, pozycja.y - this->diameter / 2);
		this->zrobHP();
		
	}

	/**
	 * @brief Funkcja odpowiadajca za rysowanie zdrowia
	 * @param cel odpowiada za okno w którym ma zostac narysowany obiekt
	 */
	void draw(sf::RenderTarget* cel) {
		cel->draw(this->hpCircle);
		cel->draw(this->sprajt);
	}

	/**
	 * @brief Funkcja odpowiedzialna za zbudowanie kuli zdrowia
	 * 
	 */
	void zrobHP() {
		this->sprajt.setPosition(this->hpPos);
		this->hpCircle.setRadius(this->diameter);
		this->hpCircle.setOrigin(this->hpPos);
		this->hpCircle.setPosition(this->hpPos);
		this->sprajt.setOrigin(this->diameter, this->diameter);
		this->hpCircle.setFillColor(sf::Color(250, 20, 20, 200));
	}

	/**
	 * @brief Funkcja odpowiedzialna za reprezentacje aktualizacji zdrowia bohatera
	 *
	 * @param obecneHP obecny stan zdrowia bohatera
	 * @param maxHP maksymalny stan zdrowia bohatera
	 */
	void updateHP(double obecneHP, double maxHP) {
		if (obecneHP < 0) obecneHP = 0;
		float procent = obecneHP / maxHP;
		this->hpCircle.setRadius(procent * this->diameter);
		this->hpCircle.setOrigin(this->hpCircle.getRadius(), this->hpCircle.getRadius());
	}

};