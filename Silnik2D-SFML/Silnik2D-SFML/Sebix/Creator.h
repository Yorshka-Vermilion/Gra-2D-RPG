#pragma once
#include "../Bartek/Stan.h"
#include "../Bartek/Gra.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Camera.h"


/**
 * @brief Klasa reprezentujaca stan gry odpowiedzialny za tworzenie postaci
 * 
 */
class Creator : public Stan
{
	/// <summary>
	/// Wskaznik na tlo reprezentujacy grafike w tle podczas tworzenia postaci
	/// </summary>
	Obiekt* bg;
	/// <summary>
	/// Wskaznik wskazujacy na gracza
	/// </summary>
	Gracz* gracz;
	/// <summary>
	/// Wskaznik na camere reprezentujaca widok na gracza
	/// </summary>
	Camera* cameraPlayer;
	/// <summary>
	/// Czcionka biblioteki sfml
	/// </summary>
	sf::Font czcionka;
	/// <summary>
	/// Nazwa uzytkownika reprezentowana przez biblioteke w formie graficznej
	/// </summary>
	sf::Text nazwa;
	/// <summary>
	/// Wartosc reprezentujaca nasycenie czerwonej barwy gracza w formie graficznej
	/// </summary> 
	sf::Text rt; 
	/// <summary>
	/// Wartosc reprezentujaca nasycenie zielonej barwy gracza w formie graficznej
	/// </summary>
	sf::Text gt;
	/// <summary>
	/// Wartosc reprezentujaca nasycenie niebieskiej barwy gracza w formie graficznej
	/// </summary>
	sf::Text bt;
	/// <summary>
	/// Wartosc reprezentujaca ilosc sila tworzonej postaci
	/// </summary>
	sf::Text sila; 
	/// <summary>
	/// Wartosc reprezentujaca ilosc magicznych obrazen tworzonej postaci
	/// </summary>
	sf::Text dmg;
	/// <summary>
	/// Wartosc reprezentujaca ilosc inteligencji tworzonej postaci
	/// </summary>
	sf::Text inteligencja;
	/// <summary>
	/// Nazwa gracza reprezentowana przez standardow¹ biblioteke wejœcia
	/// </summary>
	std::string nazwaStd = "Mag";
	/// <summary>
	/// Wartosc nasycenie barwy czerwonej w grze reprezentowana przez wartosc calkowita
	/// </summary>
	int r;
	/// <summary>
	/// Wartosc nasycenie barwy zielonej w grze reprezentowana przez wartosc calkowita
	/// </summary>
	int g;
	/// <summary>
	/// Wartosc nasycenie barwy niebieskiej w grze reprezentowana przez wartosc calkowita
	/// </summary>
	int b;
	/// <summary>
	/// Obiekt reprezentujacy w sposob graficzny prawa strzalke koloru czerwonego
	/// </summary>
	Obiekt* rr;
	/// <summary>
	/// Obiekt reprezentujacy w sposob graficzny lewa strzalke koloru czerwonego
	/// </summary>
	Obiekt* rl;
	/// <summary>
	/// Obiekt reprezentujacy w sposob graficzny prawa strzalke koloru zielonego
	/// </summary>
	Obiekt* gr;
	/// <summary>
	/// Obiekt reprezentujacy w sposob graficzny lewa strzalke koloru zielonego
	/// </summary>
	Obiekt* gl;
	/// <summary>
	/// Obiekt reprezentujacy w sposob graficzny prawa strzalke koloru niebieskiego
	/// </summary>
	Obiekt* br;
	/// <summary>
	/// Obiekt reprezentujacy w sposob graficzny lewa strzalke koloru niebieskiego
	/// </summary>
	Obiekt* bl;
	/// <summary>
	/// Obiekt reprezentujacy przycisk odpowiadajacy za dodawanie punktow zdolnosci do sily
	/// </summary>
	Obiekt* buttonSila;
	/// <summary>
	/// Obiekt reprezentujacy przycisk odpowiadajacy za dodawanie punktow zdolnosci do obrazen
	/// </summary>
	Obiekt* buttonDmg;
	/// <summary>
	/// Obiekt reprezentujacy przycisk odpowiadajacy za dodawanie punktow zdolnosci do inteligencji
	/// </summary>
	Obiekt* buttonInteligencja;
	/// <summary>
	/// Obiekt reprezentujacy przycisk odpowiadajacy za zakonczenie tworzenia postaci
	/// </summary>
	Obiekt* check;
	/// <summary>
	/// Flaga odpowiadajaca za wycofanie sie z kreatora postaci
	/// </summary>
	bool goBack = false;



public:
	/**
	 * @brief Konstruktor tworzenia nowego stanu Kreatora postaci
	 *
	 * @param window Wskaznik na okno
	 * @param stos Wskaznik na stos wskaznikow na stany
	 * @param event Wskaznik na eventy
	 */
	Creator(sf::RenderWindow* window, std::stack<Stan*>* stos, sf::Event* event) : Stan(window, stos, event) {
		this->makeCreator();
	}
	/**
	 * @brief Funkcja odpowiadajaca za zbudowanie postaci
	 */
	void makeCreator() {
		this->gracz = new Gracz("H11.png", sf::Vector2f(200, 200), 100, 300, 1000);
		this->cameraPlayer = new Camera(sf::Vector2f(window->getSize().x, window->getSize().y), 0.2);
		this->nazwa = this->zrobTekst("Bandwidth 8x8.ttf", sf::Vector2f(200, 130));
		this->rt = this->zrobTekst("Bandwidth 8x8.ttf", sf::Vector2f(85, 140));
		this->gt = this->zrobTekst("Bandwidth 8x8.ttf", sf::Vector2f(85, 190));
		this->bt = this->zrobTekst("Bandwidth 8x8.ttf", sf::Vector2f(85, 240));
		this->sila = this->zrobTekst("Bandwidth 8x8.ttf", sf::Vector2f(300, 140));
		this->dmg = this->zrobTekst("Bandwidth 8x8.ttf", sf::Vector2f(300, 190));
		this->inteligencja = this->zrobTekst("Bandwidth 8x8.ttf", sf::Vector2f(300, 240));
		this->r = this->g = this->b = 255;

		//Przyciski
		this->rr = new Obiekt("Arrowl.png", sf::Vector2f(20, 130));
		this->rl = new Obiekt("Arrowp.png", sf::Vector2f(120, 130));
		this->gr = new Obiekt("Arrowl.png", sf::Vector2f(20, 180));
		this->gl = new Obiekt("Arrowp.png", sf::Vector2f(120, 180));
		this->br = new Obiekt("Arrowl.png", sf::Vector2f(20, 230));
		this->bl = new Obiekt("Arrowp.png", sf::Vector2f(120, 230));
		this->check = new Obiekt("check.png", sf::Vector2f(0, 0));
		this->check->setOriginOnMiddle();
		this->check->przestaw(sf::Vector2f(200, 270));
		this->buttonSila = new Obiekt("plus.png", sf::Vector2f(0, 0));
		this->buttonSila->przeskaluj(sf::Vector2f(0.5, 0.5));
		this->buttonSila->setOriginOnMiddle();
		this->buttonSila->przestaw(sf::Vector2f(375, 140));
		this->buttonDmg = new Obiekt("plus.png", sf::Vector2f(0, 0));
		this->buttonDmg->przeskaluj(sf::Vector2f(0.5, 0.5));
		this->buttonDmg->setOriginOnMiddle();
		this->buttonDmg->przestaw(sf::Vector2f(375, 190));
		this->buttonInteligencja = new Obiekt("plus.png", sf::Vector2f(0, 0));
		this->buttonInteligencja->przeskaluj(sf::Vector2f(0.5, 0.5));
		this->buttonInteligencja->setOriginOnMiddle();
		this->buttonInteligencja->przestaw(sf::Vector2f(375, 240));


		this->sila.setString(std::string("Sila: ").append(std::to_string(this->gracz->statystyki->zwrocSila())));
		sf::Vector2f pozycja = this->sila.getPosition();
		sf::FloatRect center = this->sila.getLocalBounds();
		this->sila.setOrigin(center.left + center.width / 2, center.top + center.height / 2);
		this->sila.setPosition(pozycja);

		this->dmg.setString(std::string("Magic Damage: ").append(std::to_string(this->gracz->statystyki->zwrocDmg())));
		pozycja = this->dmg.getPosition();
		center = this->dmg.getLocalBounds();
		this->dmg.setOrigin(center.left + center.width / 2, center.top + center.height / 2);
		this->dmg.setPosition(pozycja);

		this->inteligencja.setString(std::string("Inteligencja: ").append(std::to_string(this->gracz->statystyki->zwrocInteligencja())));
		pozycja = this->inteligencja.getPosition();
		center = this->inteligencja.getLocalBounds();
		this->inteligencja.setOrigin(center.left + center.width / 2, center.top + center.height / 2);
		this->inteligencja.setPosition(pozycja);

		this->rt.setString(std::to_string(this->r));
		this->rt.setFillColor(sf::Color(r, this->rr->sprajt.getColor().g, this->rr->sprajt.getColor().b));
		pozycja = this->rt.getPosition();
		center = this->rt.getLocalBounds();
		this->rt.setOrigin(center.left + center.width / 2, center.top + center.height / 2);
		this->rt.setPosition(pozycja);

		this->gt.setString(std::to_string(this->g));
		this->gt.setFillColor(sf::Color(this->gr->sprajt.getColor().r, g, this->gr->sprajt.getColor().b));
		pozycja = this->gt.getPosition();
		center = this->gt.getLocalBounds();
		this->gt.setOrigin(center.left + center.width / 2, center.top + center.height / 2);
		this->gt.setPosition(pozycja);

		this->bt.setString(std::to_string(this->b));
		this->bt.setFillColor(sf::Color(this->bl->sprajt.getColor().r, this->bl->sprajt.getColor().g, b));
		pozycja = this->bt.getPosition();
		center = this->bt.getLocalBounds();
		this->bt.setOrigin(center.left + center.width / 2, center.top + center.height / 2);
		this->bt.setPosition(pozycja);

		//Background
		this->bg = new Obiekt("background.png", sf::Vector2f(0, 0));
		this->bg->setOriginOnMiddle();
		this->bg->przestaw(sf::Vector2f(990, 300));
		this->bg->przeskaluj(sf::Vector2f(5, 5));
	}
	/**
	 * @brief Funkcja odpowiadajaca za dodawanie nasycenia koloru czerwonego
	 */
	void addR(bool kiedy) {
		if (kiedy == true && this->r < 255 && this->rl->sprajt.getGlobalBounds().contains(this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).x, this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).y)) {
			this->r++;
			this->rt.setFillColor(sf::Color(r, 0, 0));
			this->rt.setString(std::to_string(this->r));
			sf::Vector2f pozycja = this->rt.getPosition();
			sf::FloatRect center = this->rt.getLocalBounds();
			this->rt.setOrigin(center.left + center.width / 2, center.top + center.height / 2);
			this->rt.setPosition(pozycja);
		}
	}
	/**
	 * @brief Funkcja odpowiadajaca za odejmowanie nasycenia koloru czerwonego
	 */
	void subR(bool kiedy) {
		if (kiedy == true && this->r > 0 && this->rr->sprajt.getGlobalBounds().contains(this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).x, this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).y)) {
			this->r--;
			this->rt.setFillColor(sf::Color(r, 0, 0));
			this->rt.setString(std::to_string(this->r));
			sf::Vector2f pozycja = this->rt.getPosition();
			sf::FloatRect center = this->rt.getLocalBounds();
			this->rt.setOrigin(center.left + center.width / 2, center.top + center.height / 2);
			this->rt.setPosition(pozycja);
		}
	}
	/**
	 * @brief Funkcja odpowiadajaca za dodawanie nasycenia koloru zielonego
	 */
	void addG(bool kiedy) {
		if (kiedy == true && this->g < 255 && this->gl->sprajt.getGlobalBounds().contains(this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).x, this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).y)) {
			this->g++;
			this->gt.setFillColor(sf::Color(0, g, 0));
			this->gt.setString(std::to_string(this->g));
			sf::Vector2f pozycja = this->gt.getPosition();
			sf::FloatRect center = this->gt.getLocalBounds();
			this->gt.setOrigin(center.left + center.width / 2, center.top + center.height / 2);
			this->gt.setPosition(pozycja);
		}
	}
	/**
	 * @brief Funkcja odpowiadajaca za odejmowanie nasycenia koloru zielonego
	 */
	void subG(bool kiedy) {
		if (kiedy == true && this->g > 0 && this->gr->sprajt.getGlobalBounds().contains(this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).x, this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).y)) {
			this->g--;
			this->gt.setFillColor(sf::Color(0, g, 0));
			this->gt.setString(std::to_string(this->g)); 
			sf::Vector2f pozycja = this->gt.getPosition();
			sf::FloatRect center = this->gt.getLocalBounds();
			this->gt.setOrigin(center.left + center.width / 2, center.top + center.height / 2);
			this->gt.setPosition(pozycja);
		}
	}
	/**
	 * @brief Funkcja odpowiadajaca za dodawanie nasycenia koloru niebieskiego
	 */
	void addB(bool kiedy) {
		if (kiedy == true && this->b < 255 && this->bl->sprajt.getGlobalBounds().contains(this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).x, this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).y)) {
			this->b++;
			this->bt.setFillColor(sf::Color(0, 0, b));
			this->bt.setString(std::to_string(this->b));
			sf::Vector2f pozycja = this->bt.getPosition();
			sf::FloatRect center = this->bt.getLocalBounds();
			this->bt.setOrigin(center.left + center.width / 2, center.top + center.height / 2);
			this->bt.setPosition(pozycja);
		}
	}
	/**
	 * @brief Funkcja odpowiadajaca za odejmowanie nasycenia koloru niebieskiego
	 */
	void subB(bool kiedy) {
		if (kiedy == true && this->b > 0 && this->br->sprajt.getGlobalBounds().contains(this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).x, this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).y)) {
			this->b--;
			this->bt.setFillColor(sf::Color(0, 0, b));
			this->bt.setString(std::to_string(this->b));
			sf::Vector2f pozycja = this->bt.getPosition();
			sf::FloatRect center = this->bt.getLocalBounds();
			this->bt.setOrigin(center.left + center.width / 2, center.top + center.height / 2);
			this->bt.setPosition(pozycja);
		}
	}
	/**
	 * @brief Funkcja sprawdza czy postac jest gotowa do utworzenia
	 */
	void checkCharacter(bool kiedy) {
		if (kiedy == true && this->check->sprajt.getGlobalBounds().contains(this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).x, this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).y)){
			if (this->gracz->statystyki->zwrocIloscDostepnychPunktow() == 0){
				this->gracz->setFullZycie();
				this->gracz->setFullMana();
				this->stos->push(new Gra(window, stos, event,this->gracz));
				this->goBack = true;
			}
			else {
				std::cout << "Wydaj pozosta³e punkty umiejetnosci!" << std::endl;
			}
		}
	}
	/**
	 * @brief Dekonstruktor kreatora
	 */
	~Creator() {
		delete(this->rr);
		delete(this->rl);
		delete(this->gr);
		delete(this->gl);
		delete(this->br);
		delete(this->bl);
		delete(this->bg);
		delete(this->buttonSila);
		delete(this->buttonDmg);
		delete(this->buttonInteligencja);
		delete(this->check);
		delete(this->cameraPlayer);
		delete(this->gracz);
		delete(this->event);
		delete(this->stos);
		delete(this->window);
	}
	/**
	 * @brief Rysowanie obiektow na ekranie
	 *
	 * @param target Wskaznik na cel rysowania
	 */
	void draw(sf::RenderTarget* target) { // Rysowanie obiektow na ekranie
		if (!target) target = this->window;
		this->bg->draw(target);
		target->setView(this->cameraPlayer->returnView());
		this->gracz->draw(target);
		target->draw(this->nazwa);

		this->buttonSila->draw(target);
		target->draw(this->sila);
		this->buttonDmg->draw(target);
		target->draw(this->dmg);
		this->buttonInteligencja->draw(target);
		target->draw(this->inteligencja);
		this->check->draw(target);
		this->rr->draw(target);
		this->rl->draw(target);
		target->draw(this->rt);
		this->gr->draw(target);
		this->gl->draw(target);
		target->draw(this->gt);
		this->br->draw(target);
		this->bl->draw(target);
		target->draw(this->bt);

		target->setView(target->getDefaultView());
	};
	/**
	 * @brief Odswiezenie stanu gry
	 *
	 * @param dtime Delta czasu (timer)
	 */
	void update(const float& dtime) { // Odswiezenie stanu aktualnego "stanu"
		if (this->goBack == true) this->stos->pop();
		this->dtime = dtime;
		
		this->cameraPlayer->update(this->gracz);
		sprawdzMysz();
		while (this->window->pollEvent(*this->event)) {
			if (this->lewy == true && this->buttonSila->sprajt.getGlobalBounds().contains(this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).x, this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).y) && this->gracz->statystyki->zwrocIloscDostepnychPunktow()>0) {
				this->gracz->statystyki->dodajSila();
				this->gracz->maxZycie = this->gracz->maxZycie + this->gracz->statystyki->obliczSila(this->gracz->maxZycie);
				this->sila.setString(std::string("Sila: ").append(std::to_string(this->gracz->statystyki->zwrocSila())));
			}
			if (this->lewy == true && this->buttonDmg->sprajt.getGlobalBounds().contains(this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).x, this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).y) && this->gracz->statystyki->zwrocIloscDostepnychPunktow() > 0) {
				this->gracz->statystyki->dodajDmg();
				this->gracz->statystyki->mnoznikDmg = 0.1 * this->gracz->statystyki->zwrocDmg();
				this->dmg.setString(std::string("Magic Damage: ").append(std::to_string(this->gracz->statystyki->zwrocDmg())));
			}
			if (this->lewy == true && this->buttonInteligencja->sprajt.getGlobalBounds().contains(this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).x, this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).y) && this->gracz->statystyki->zwrocIloscDostepnychPunktow() > 0) {
				this->gracz->statystyki->dodajInteligencja();
				this->gracz->maxMana = this->gracz->maxMana + this->gracz->statystyki->obliczInteligencja(this->gracz->maxMana);
				this->inteligencja.setString(std::string("Inteligencja: ").append(std::to_string(this->gracz->statystyki->zwrocInteligencja())));
			}

			if (this->event->type == sf::Event::KeyPressed) {
				if (this->event->key.code == sf::Keyboard::BackSpace) {
					if (!this->nazwaStd.empty())this->nazwaStd.pop_back();
					break;
				}
				else if ((this->event->key.code == sf::Keyboard::Space) && (this->nazwaStd.size() < 10)) {
					this->nazwaStd.push_back(' ');
					this->nazwaStd.pop_back();
				}
				else if (this->event->key.code == sf::Keyboard::Escape) {
					this->goBack = true;
				}
			}
			else if ((this->event->type == sf::Event::TextEntered) && (this->nazwaStd.size() < 10)) {
				char x = char(this->event->key.code);
				this->nazwaStd.push_back(x);
			}
		}
		this->nazwa.setString(this->nazwaStd);
		sf::Vector2f pozycja = this->nazwa.getPosition();
		sf::FloatRect center = this->nazwa.getLocalBounds();
		this->nazwa.setOrigin(center.left + center.width / 2, center.top + center.height / 2);
		this->nazwa.setPosition(pozycja);
		this->gracz->nazwa = nazwaStd;
		addR(this->lewy);
		subR(this->lewy);
		addG(this->lewy);
		subG(this->lewy);
		addB(this->lewy);
		subB(this->lewy);
		this->gracz->sprajt.setColor(sf::Color(this->r, this->g, this->b));
		checkCharacter(this->lewy);
	};
	/**
	 * @brief Odswiezenie stanu gry
	 *
	 * @param sciezka Sciezka odpowiedzialna za wskazanie czcionki
	 * @param pozycja Pozycja reprezetnujaca pozycje napisow w przestrzeni
	 */
	sf::Text zrobTekst(std::string sciezka, sf::Vector2f pozycja) {
		if (!this->czcionka.loadFromFile(sciezka)) {
			std::cout << "Nie udalo sie zaladowac czcionki" << std::endl;
		}
		sf::Text text;
		text.setFont(czcionka);
		text.setFillColor(sf::Color::White);
		text.setOutlineColor(sf::Color::Black);
		text.setCharacterSize(80);
		text.setOutlineThickness(4);
		text.scale(0.1, 0.1);
		sf::FloatRect center = nazwa.getLocalBounds();
		text.setOrigin(center.left + center.width / 2, center.top + center.height / 2);
		text.setPosition(pozycja);
		return text;
	}

};


