#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../Bartek/Gracz.h"
#include "Zycie.h"
#include "Mana.h"
#include "Exp.h"
#include "StatInGame.h"

class HUD {
	Gracz* gracz;
	Zycie* zycie;
	Mana* mana;
	Exp* exp;
	StatInGame* statystykiWGrze;
	
	bool isAble = false;
	sf::Font czcionka;
	sf::Text level;

public:

	HUD(sf::Vector2f pozycja, Gracz* gracz) {
		this->gracz = gracz;
		this->zycie = new Zycie("circle.png", pozycja);
		this->mana = new Mana("circle.png", sf::Vector2f(0,pozycja.y));
		this->exp = new Exp("circle.png", pozycja);
		this->zrobTekst("Bandwidth 8x8.ttf", sf::Vector2f(pozycja.x / 2, pozycja.y - 130));
		this->statystykiWGrze = new StatInGame(this->gracz->statystyki->zwrocSila(), this->gracz->statystyki->zwrocDmg(), this->gracz->statystyki->zwrocInteligencja());
	}

	~HUD() {
		delete(this->gracz);
		delete(this->statystykiWGrze);
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
		if (this->gracz->statystyki->zwrocIloscDostepnychPunktow() > 0) {
			this->statystykiWGrze->draw(target);
			this->isAble = true;
		}
		else this->isAble = false;
	}

	bool returnIsAble() {
		return this->isAble;
	}

	bool changeIsAble() {
		if (!this->isAble) this->isAble = true;
		else this->isAble = false;
	}

	Obiekt* zwrocDoSily() {
		return this->statystykiWGrze->zwrocPrzyciskSila();
	}

	Obiekt* zwrocDoDmg() {
		return this->statystykiWGrze->zwrocPrzyciskDmg();
	}

	Obiekt* zwrocDoInteligencji() {
		return this->statystykiWGrze->zwrocPrzyciskInteligencja();
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
			this->gracz->statystyki->zwiekszPunkty();
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

	bool sprawdzajPodswietlenia(sf::Vector2f mysz,bool lewy) { //Za duzo razy wykonuje sie nacisniecie
			if (!this->statystykiWGrze->zwrocOkno()->sprajt.getGlobalBounds().contains(mysz.x, mysz.y)) {
				this->przyciemnijSila();
				this->przyciemnijDmg();
				this->przyciemnijInteligencja();
				return false;
			}
			else {
				if (this->zwrocDoSily()->sprajt.getGlobalBounds().contains(mysz.x, mysz.y)) {
					this->podswietlSila();
					if (lewy == true && this->gracz->statystyki->zwrocIloscDostepnychPunktow() > 0) {
						this->gracz->statystyki->dodajSila();
						this->gracz->maxZycie = this->gracz->maxZycie + this->gracz->statystyki->obliczSila(this->gracz->maxZycie);
						this->statystykiWGrze->aktualizujSila("Sila: ", this->gracz->statystyki->zwrocSila());
						this->gracz->setFullZycie();

					}
				}
				else this->przyciemnijSila();

				if (this->zwrocDoDmg()->sprajt.getGlobalBounds().contains(mysz.x, mysz.y)) {
					this->podswietlDmg();
					if (lewy == true && this->gracz->statystyki->zwrocIloscDostepnychPunktow() > 0) {
						this->gracz->statystyki->dodajDmg();
						this->gracz->statystyki->mnoznikDmg = 0.1 * this->gracz->statystyki->zwrocDmg();
						this->statystykiWGrze->aktualizujDmg("Magic Damage: ", this->gracz->statystyki->zwrocDmg());
					}
				}
				else this->przyciemnijDmg();

				if (this->zwrocDoInteligencji()->sprajt.getGlobalBounds().contains(mysz.x, mysz.y)) {
					this->podswietlInteligencja();
					if (lewy == true && this->gracz->statystyki->zwrocIloscDostepnychPunktow() > 0) {
						this->gracz->statystyki->dodajInteligencja();
						this->gracz->maxMana = this->gracz->maxMana + this->gracz->statystyki->obliczInteligencja(this->gracz->maxMana);
						this->statystykiWGrze->aktualizujInteligencja("Inteligencja: ", this->gracz->statystyki->zwrocInteligencja());
						this->gracz->setFullMana();
					}
				}
				else this->przyciemnijInteligencja();
				return true;
		}
	}

	void przyciemnijSila() {
		if (this->statystykiWGrze->sila.getFillColor().a <=125) return;
		this->statystykiWGrze->zwrocPrzyciskSila()->sprajt.setColor(sf::Color(255, 255, 255, this->statystykiWGrze->zwrocPrzyciskSila()->sprajt.getColor().a - 1));
		this->statystykiWGrze->sila.setFillColor(sf::Color(255, 255, 255, this->statystykiWGrze->sila.getFillColor().a - 1));
	}

	void podswietlSila() {
		if (this->statystykiWGrze->sila.getFillColor().a >= 230) return;
		this->statystykiWGrze->zwrocPrzyciskSila()->sprajt.setColor(sf::Color(255, 255, 255, this->statystykiWGrze->zwrocPrzyciskSila()->sprajt.getColor().a + 1));
		this->statystykiWGrze->sila.setFillColor(sf::Color(255, 255, 255, this->statystykiWGrze->sila.getFillColor().a + 1));
	}

	void przyciemnijDmg() {
		if (this->statystykiWGrze->dmg.getFillColor().a <= 125) return;
		this->statystykiWGrze->zwrocPrzyciskDmg()->sprajt.setColor(sf::Color(255, 255, 255, this->statystykiWGrze->zwrocPrzyciskDmg()->sprajt.getColor().a - 1));
		this->statystykiWGrze->dmg.setFillColor(sf::Color(255, 255, 255, this->statystykiWGrze->dmg.getFillColor().a - 1));
	}

	void podswietlDmg() {
		if (this->statystykiWGrze->dmg.getFillColor().a >= 230) return;
		this->statystykiWGrze->zwrocPrzyciskDmg()->sprajt.setColor(sf::Color(255, 255, 255, this->statystykiWGrze->zwrocPrzyciskDmg()->sprajt.getColor().a + 1));
		this->statystykiWGrze->dmg.setFillColor(sf::Color(255, 255, 255, this->statystykiWGrze->dmg.getFillColor().a + 1));
	}

	void przyciemnijInteligencja() {
		if (this->statystykiWGrze->inteligencja.getFillColor().a <= 125) return;
		this->statystykiWGrze->zwrocPrzyciskInteligencja()->sprajt.setColor(sf::Color(255, 255, 255, this->statystykiWGrze->zwrocPrzyciskInteligencja()->sprajt.getColor().a - 1));
		this->statystykiWGrze->inteligencja.setFillColor(sf::Color(255, 255, 255, this->statystykiWGrze->inteligencja.getFillColor().a - 1));
	}

	void podswietlInteligencja() {
		if (this->statystykiWGrze->inteligencja.getFillColor().a >= 230) return;
		this->statystykiWGrze->zwrocPrzyciskInteligencja()->sprajt.setColor(sf::Color(255, 255, 255, this->statystykiWGrze->zwrocPrzyciskInteligencja()->sprajt.getColor().a + 1));
		this->statystykiWGrze->inteligencja.setFillColor(sf::Color(255, 255, 255, this->statystykiWGrze->inteligencja.getFillColor().a + 1));
	}

	void przyciemnijOkno() {
		if (this->statystykiWGrze->zwrocOkno()->sprajt.getColor().a <= 75) return;
		this->statystykiWGrze->zwrocOkno()->sprajt.setColor(sf::Color(255, 255, 255, this->statystykiWGrze->zwrocPrzyciskInteligencja()->sprajt.getColor().a - 1));
	}

	void podswietlOkno() {
		if (this->statystykiWGrze->zwrocOkno()->sprajt.getColor().a >= 255) return;
		this->statystykiWGrze->zwrocOkno()->sprajt.setColor(sf::Color(255, 255, 255, this->statystykiWGrze->zwrocPrzyciskInteligencja()->sprajt.getColor().a + 1));
	}
};

