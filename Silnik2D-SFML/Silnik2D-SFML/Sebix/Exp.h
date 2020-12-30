#pragma once
#include "../Bartek/Obiekt.h"
#include "Funkcje.h"

class Exp : public Obiekt {
	float diameter;
	int maxOrbs = 9;
	int activeOrb = 0;
	float orbGate = 0;
	sf::Vector2f expMid;
	std::vector<sf::CircleShape> expCircle;


public:
	Exp(std::string sciezka, sf::Vector2f pozycja) : Obiekt(sciezka, pozycja) {
		this->diameter = 25;
		this->expMid = sf::Vector2f(pozycja.x/2,pozycja.y - 50);
		this->orbGate = 1 / (float)maxOrbs;
		for(int i = 0; i< this->maxOrbs; i++)
			expCircle.push_back(sf::CircleShape(0));
		this->zrobExp();
	}

	void draw(sf::RenderTarget* cel) {
		for (int i = 0; i < this->maxOrbs; i++)
			cel->draw(this->expCircle[i]);
		cel->draw(this->sprajt);
	}

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

	void updateExp(double obecneExp, double maxExp, bool levelUp) {
		float procent = obecneExp / maxExp;
		if(activeOrb >= 0 && activeOrb < this->maxOrbs){
			//float equalizer = this->diameter / (procent * this->diameter);
			//std::cout << "Full " << procent << " Orb " << this->orbGate << " Max " << this->maxOrbs << " Active " << this->activeOrb << " Equalizer " << equalizer << std::endl;
			//this->expCircle[activeOrb].setRadius(procent*(this->diameter*equalizer));
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






