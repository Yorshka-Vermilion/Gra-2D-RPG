#pragma once
#include "../Bartek/Obiekt.h";

class Mana : public Obiekt {
	float diameter;
	sf::Vector2f manaPos;
	sf::CircleShape manaCircle;
public:
	Mana(std::string sciezka, sf::Vector2f pozycja) : Obiekt(sciezka, pozycja) {
		this->diameter = 100;
		this->manaPos = sf::Vector2f(pozycja.x + this->diameter / 2, pozycja.y - this->diameter / 2);
		this->zrobMana();

	}

	void draw(sf::RenderTarget* cel) {
		cel->draw(this->manaCircle);
		cel->draw(this->sprajt);
	}

	void zrobMana() {
		this->sprajt.setPosition(this->manaPos);
		this->manaCircle.setRadius(this->diameter);
		this->manaCircle.setOrigin(this->manaPos);
		this->manaCircle.setPosition(this->manaPos);
		this->sprajt.setOrigin(this->diameter, this->diameter);
		this->manaCircle.setFillColor(sf::Color(26, 140, 204, 200));
	}

	void updateMana(double obecnaMana, double maxMana) {
		float procent = obecnaMana / maxMana;
		this->manaCircle.setRadius(procent * this->diameter);
		this->manaCircle.setOrigin(this->manaCircle.getRadius(), this->manaCircle.getRadius());
	}

};