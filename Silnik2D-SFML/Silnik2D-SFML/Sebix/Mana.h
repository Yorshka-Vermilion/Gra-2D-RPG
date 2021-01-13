#pragma once
#include "../Bartek/Obiekt.h";

/**
 * @brief Klasa odpowiada za reprezentacje graficzna many bohatera
 *
 */
class Mana : public Obiekt {
	/// <summary>
	/// Wartosc okreslajaca srednice okregu
	/// </summary>
	float diameter;
	/// <summary>
	/// Pozycja many bohatera
	/// </summary>
	sf::Vector2f manaPos;
	/// <summary>
	/// Obiekt reprezentujacy kule many bohatera
	/// </summary>
	sf::CircleShape manaCircle;
public:
	/**
	 * @brief Konstruktor odpowiedzialny za zbudowanie many
	 *
	 * @param sciezka odpowiada za znajdowanie sie pliku reprezentujacego mane
	 * @param pozycja odpowaida za pozycje w ktorej ma sie znajdowac mane
	 */
	Mana(std::string sciezka, sf::Vector2f pozycja) : Obiekt(sciezka, pozycja) {
		this->diameter = 100;
		this->manaPos = sf::Vector2f(pozycja.x + this->diameter / 2, pozycja.y - this->diameter / 2);
		this->zrobMana();

	}
	/**
	 * @brief Funkcja odpowiadajca za rysowanie many
	 * @param cel odpowiada za okno w którym ma zostac narysowany obiekt
	 */
	void draw(sf::RenderTarget* cel) {
		cel->draw(this->manaCircle);
		cel->draw(this->sprajt);
	}
	/**
	 * @brief Funkcja odpowiedzialna za zbudowanie kuli many
	 *
	 */
	void zrobMana() {
		this->sprajt.setPosition(this->manaPos);
		this->manaCircle.setRadius(this->diameter);
		this->manaCircle.setOrigin(this->manaPos);
		this->manaCircle.setPosition(this->manaPos);
		this->sprajt.setOrigin(this->diameter, this->diameter);
		this->manaCircle.setFillColor(sf::Color(26, 140, 204, 200));
	}
	/**
	 * @brief Funkcja odpowiedzialna za reprezentacje aktualizacji many bohatera
	 *
	 * @param obecnaMana obecny stan many bohatera
	 * @param maxMana maksymalny stan many bohatera
	 */
	void updateMana(double obecnaMana, double maxMana) {
		if (obecnaMana < 0) obecnaMana = 0;
		float procent = obecnaMana / maxMana;
		this->manaCircle.setRadius(procent * this->diameter);
		this->manaCircle.setOrigin(this->manaCircle.getRadius(), this->manaCircle.getRadius());
	}

};