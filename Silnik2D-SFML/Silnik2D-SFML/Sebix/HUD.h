#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../Bartek/Gracz.h"
#include "../Bartek/Obiekt.h"

class HUD : public Obiekt {
	Gracz* gracz;
	sf::RectangleShape hudBack;
	sf::RectangleShape hpBar;
	sf::RectangleShape manaBar;
	sf::RectangleShape expBarL, expBarR, expBarM;
	sf::Vector2f hpSize;
	sf::Vector2f manaSize;
	sf::Vector2f expSizeL, expSizeR, expSizeM;
	sf::Font czcionka;
	sf::Text level;
	double exp;

public:

	HUD(std::string sciezka, sf::Vector2f pozycja, Gracz* gracz) : Obiekt(sciezka, pozycja) {
		this->gracz = gracz;
		zrobHUD(pozycja);
	}

	void update() {
		updateHP();
		updateMana();
		updateExp();
	}

	void draw(sf::RenderTarget* target) {
		target->draw(this->hudBack);
		target->draw(this->expBarL);
		target->draw(this->expBarR);
		target->draw(this->expBarM);
		target->draw(this->hpBar);
		target->draw(this->manaBar);
		target->draw(this->sprajt);
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
		level.setCharacterSize(80);
		level.setOutlineThickness(4);
		sf::FloatRect center = level.getLocalBounds();
		level.setOrigin(center.left + center.width / 2, center.top + center.height / 2);
		level.setPosition(pozycja);
	}

	void zrobHUD(sf::Vector2f pozycja) {
		int hudX = this->sprajt.getTexture()->getSize().x;
		int hudY = this->sprajt.getTexture()->getSize().y;
		this->sprajt.setOrigin(hudX, hudY);
		this->sprajt.setPosition(pozycja);
		this->hudBack.setFillColor(sf::Color::White);
		this->hudBack.setSize(sf::Vector2f(hudX, hudY));
		this->hudBack.setOrigin(hudX, hudY);
		this->hudBack.setPosition(pozycja);

		this->zrobHP(pozycja);
		this->zrobMane(pozycja);
		this->zrobExp(pozycja);
		this->zrobTekst("Bandwidth 8x8.ttf", sf::Vector2f(pozycja.x / 2, pozycja.y - 130));
	}

	void zrobHP(sf::Vector2f pozycja) {
		this->hpBar.setSize(sf::Vector2f(400, 400));
		this->hpSize = this->hpBar.getSize();
		this->hpBar.setPosition(0, pozycja.y);
		this->hpBar.setFillColor(sf::Color(250, 20, 20, 200));
	}

	void updateHP() {
		double procent = -this->gracz->zwrocObecnyStanZdrowia() / this->gracz->maxZycie;
		this->hpBar.setSize(sf::Vector2f(this->hpSize.x, std::floor(this->hpSize.y * procent)));
	}

	void zrobMane(sf::Vector2f pozycja) {
		this->manaBar.setSize(sf::Vector2f(400, 400));

		this->manaSize = this->manaBar.getSize();

		this->manaBar.setOrigin(this->manaSize.x, 0);
		this->manaBar.setPosition(pozycja);
		this->manaBar.setFillColor(sf::Color(26, 140, 204, 200));
	}

	void updateMana() {
		double procent = -this->gracz->zwrocObecnyStanMany() / this->gracz->maxMana;
		this->manaBar.setSize(sf::Vector2f(this->manaSize.x, std::floor(this->manaSize.y * procent)));
	}

	void zrobExp(sf::Vector2f pozycja) {
		this->expBarL.setSize(sf::Vector2f(500, 300));
		this->expSizeL = this->expBarL.getSize();
		this->expBarL.setFillColor(sf::Color(245, 223, 137, 200));
		this->expBarL.setPosition(hpSize.x, pozycja.y - expSizeL.y);

		this->expBarR.setSize(sf::Vector2f(500, 300));
		this->expSizeR = this->expBarR.getSize();
		this->expBarR.setFillColor(sf::Color(245, 223, 137, 200));
		this->expBarR.setPosition(pozycja.x - manaSize.x, pozycja.y - expSizeR.y);

		this->expBarM.setSize(sf::Vector2f(130, 240));
		this->expSizeM = this->expBarM.getSize();
		this->expBarM.setPosition((pozycja.x / 2) - (this->expSizeM.x / 2), pozycja.y);
		this->expBarM.setFillColor(sf::Color(245, 223, 137, 200));
	}

	void updateExpL() {
		double procent = this->gracz->zwrocObecnyStanExp() / (this->gracz->maxExp * 0.66);
		this->expBarL.setSize(sf::Vector2f(std::floor(this->expSizeL.x * procent), this->expSizeL.y));
	}

	void updateExpR() {
		double procent = -this->gracz->zwrocObecnyStanExp() / (this->gracz->maxExp * 0.66);
		this->expBarR.setSize(sf::Vector2f(std::floor(this->expSizeR.x * procent), this->expSizeR.y));
	}

	void updateExpM() {
		double procent = ((this->gracz->maxExp * 0.66) - this->gracz->zwrocObecnyStanExp()) / (this->gracz->maxExp * 0.34);
		this->expBarM.setSize(sf::Vector2f(this->expSizeM.x, std::floor(this->expSizeM.y * procent)));
	}

	void updateExp() {
		this->exp = this->gracz->zwrocObecnyStanExp() / this->gracz->maxExp;
		if (this->gracz->levelUp == true) {
			updateLevel();
			this->expBarM.setSize(sf::Vector2f(this->expSizeM.x, 20));
		}
		else if (this->exp >= 0.66) {
			updateExpM();
		}
		else {
			updateExpL();
			updateExpR();
		}
	}

	void updateLevel() {
		this->level.setString(std::to_string(this->gracz->zwrocLevel()));
		this->gracz->zmienStanLevel();
	}
};

