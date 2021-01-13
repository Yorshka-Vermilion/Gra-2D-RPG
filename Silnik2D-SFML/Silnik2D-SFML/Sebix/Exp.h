#pragma once
#include "../Bartek/Obiekt.h"
#include "Funkcje.h"

/**
 * @brief Klasa odpowiada za reprezentacje graficzna doœwiadczenia bohatera
 *
 */
class Exp : public Obiekt {	
	/// <summary>
	/// Wartosc okreslajaca srednice okregu
	/// </summary>
	float diameter;
	/// <summary>
	/// Wartosc okreslajaca maksymalna ilosc kul z doswiadczeniem
	/// </summary>
	int maxOrbs = 9;
	/// <summary>
	/// Ilosc uzupelnionych kul doswiadczenia
	/// </summary>
	int activeOrb = 0;
	/// <summary>
	/// Wartosc graniczna przy ktorej postac wbije wy¿szy poziom
	/// </summary>
	float orbGate = 0;
	/// <summary>
	/// Pozycja srodkowej kuli doswiadczenia
	/// </summary>
	sf::Vector2f expMid;
	/// <summary>
	/// Obiekt reprezentujacy kulki doswiadczenia bohatera
	/// </summary>
	std::vector<sf::CircleShape> expCircle;


public:
	/**
	 * @brief Konstruktor odpowiedzialny za zbudowanie kul z doswiadczeniem
	 *
	 * @param sciezka odpowiada za znajdowanie sie pliku reprezentujacego kule doswiadczenia
	 * @param pozycja odpowaida za pozycje w ktorej ma sie znajdowac srodkowa kula z doswiadczeniem
	 */
	Exp(std::string sciezka, sf::Vector2f pozycja) : Obiekt(sciezka, pozycja) {
		this->diameter = 25;
		this->expMid = sf::Vector2f(pozycja.x/2,pozycja.y - 50);
		this->orbGate = 1 / (float)maxOrbs;
		for(int i = 0; i< this->maxOrbs; i++)
			expCircle.push_back(sf::CircleShape(0));
		this->zrobExp();
	}
	/**
	* @brief Funkcja odpowiadajca za rysowanie doswiadczenia
	* @param cel odpowiada za okno w którym ma zostac narysowany obiekt
	*/
	void draw(sf::RenderTarget* cel) {
		for (int i = 0; i < this->maxOrbs; i++)
			cel->draw(this->expCircle[i]);
		cel->draw(this->sprajt);
	}
	/**
	 * @brief Funkcja odpowiedzialna za zbudowanie kul doswiadczenia
	 *
	 */
	void zrobExp() {
		for(int i = 0; i <= this->maxOrbs/2; i++) {
			this->expCircle[i].setOrigin(this->expMid);
			this->expCircle[i].setPosition(this->expMid.x - (80*i), this->expMid.y);
			this->expCircle[i].setFillColor(sf::Color(245, 223, 137, 250));

			this->expCircle[i + this->maxOrbs/2].setOrigin(this->expMid);
			this->expCircle[i + this->maxOrbs/2].setPosition(this->expMid.x + (80 * i), this->expMid.y);
			this->expCircle[i + this->maxOrbs/2].setFillColor(sf::Color(245, 223, 137, 250));
		}
	}
	/**
	 * @brief Funkcja odpowiedzialna za reprezentacje aktualizacji doswiadczenia bohatera
	 *
	 * @param obecneExp obecny stan doswiadczenia bohatera
	 * @param maxExp maksymalny stan doswiadczenia bohatera
	 * @param levelUp flaga reprezentujaca wbicie poziomu przez bohatera
	 */
	void updateExp(double obecneExp, double maxExp, bool levelUp) {
		if (obecneExp < 0) obecneExp = 0;
		else if (obecneExp > maxExp) obecneExp = maxExp;
		float procent = obecneExp / maxExp;
		if(activeOrb >= 0 && activeOrb < this->maxOrbs){
			this->expCircle[activeOrb].setRadius(procent * this->diameter);
			this->expCircle[activeOrb].setOrigin(this->expCircle[activeOrb].getRadius(), this->expCircle[activeOrb].getRadius());
			if (levelUp == true) {
				this->activeOrb = 0;
				for (int i = 0; i < this->maxOrbs; i++)
					this->expCircle[i].setRadius(0);
				}
			else if (procent >= orbGate * (activeOrb + 1))this->activeOrb++;
		}
		
	}

};
