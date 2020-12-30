#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../Bartek/Gracz.h"
#include "Zycie.h"
#include "Mana.h"
#include "Exp.h"

class HUD {
	Gracz* gracz;
	Zycie* zycie;
	Mana* mana;
	Exp* exp;

	sf::Font czcionka;
	sf::Text level;

public:

	HUD(sf::Vector2f pozycja, Gracz* gracz) {
		this->gracz = gracz;
		this->zycie = new Zycie("circle.png", pozycja);
		this->mana = new Mana("circle.png", sf::Vector2f(0,pozycja.y));
		this->exp = new Exp("circle.png", pozycja);
		this->zrobTekst("Bandwidth 8x8.ttf", sf::Vector2f(pozycja.x / 2, pozycja.y - 130));
	}

	~HUD() {
		delete(this->gracz);
		delete(this->zycie);
		delete(this->mana);
		delete(this->exp);
	}

	void update() {
		this->zycie->updateHP(this->gracz->zwrocObecnyStanZdrowia(), this->gracz->maxZycie);
		this->mana->updateMana(this->gracz->zwrocObecnyStanMany(), this->gracz->maxMana);
		this->updateExp();
	}

	void draw(sf::RenderTarget* target) {
		this->zycie->draw(target);
		this->mana->draw(target);
		this->exp->draw(target);
		target->draw(this->level);
	}

	void zrobTekst(std::string sciezka, sf::Vector2f pozycja) {
		if (!this->czcionka.loadFromFile(sciezka)) {
			std::cout << "Nie udalo sie zaladowac czcionki" << std::endl;
		}
		level.setFont(czcionka);
		level.setString(std::to_string(this->gracz->level));
		level.setFillColor(sf::Color::White);
		level.setOutlineColor(sf::Color::Black);
		level.setCharacterSize(40);
		level.setOutlineThickness(4);
		sf::FloatRect center = level.getLocalBounds();
		level.setOrigin(center.left + center.width / 2, center.top + center.height / 2);
		level.setPosition(pozycja);
	}

	void updateExp() {
		this->exp->updateExp(this->gracz->zwrocObecnyStanExp(), this->gracz->maxExp, this->gracz->levelUp);
		if (this->gracz->levelUp == true) {
			updateLevel();
		}
	}

	void updateLevel() {
		this->level.setString(std::to_string(this->gracz->zwrocLevel()));
		this->gracz->zmienStanLevel();
		sf::Vector2f pozycja = this->level.getPosition();
		sf::FloatRect center = this->level.getLocalBounds();
		level.setOrigin(center.left + center.width / 2, center.top + center.height / 2);
		level.setPosition(pozycja);
	}
};

