#pragma once
#include "../Bartek/Obiekt.h";

class Zycie : public Obiekt {
	float diameter;
	sf::Vector2f hpPos;
	sf::CircleShape hpCircle;
public:
	Zycie(std::string sciezka, sf::Vector2f pozycja) : Obiekt(sciezka, pozycja) {
		this->diameter = 100;
		this->hpPos = sf::Vector2f(pozycja.x-this->diameter /2, pozycja.y - this->diameter / 2);
		this->zrobHP();
		
	}

	void draw(sf::RenderTarget* cel) {
		cel->draw(this->hpCircle);
		cel->draw(this->sprajt);
	}

	void zrobHP() {
		this->sprajt.setPosition(this->hpPos);
		this->hpCircle.setRadius(this->diameter);
		this->hpCircle.setOrigin(this->hpPos);
		this->hpCircle.setPosition(this->hpPos);
		this->sprajt.setOrigin(this->diameter, this->diameter);
		this->hpCircle.setFillColor(sf::Color(250, 20, 20, 200));
	}

	void updateHP(double obecneHP, double maxHP) {
		float procent = obecneHP / maxHP;
		this->hpCircle.setRadius(procent * this->diameter);
		this->hpCircle.setOrigin(this->hpCircle.getRadius(), this->hpCircle.getRadius());
	}

};