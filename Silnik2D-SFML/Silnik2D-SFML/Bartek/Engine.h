#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include "../Sebix.h"
#include "../Bartek.h"
#include "../Przemek.h"

/**
* @brief Glowna klasa silnika
*/

class Engine
{
private:
	/// Szerokosc okna
	float window_width;
	/// Wysokosc okna
	float window_height;
	/// Zmienna uzywana do kontroli czasu
	float dtime;
	/// Okno
	sf::RenderWindow* window;
	/// Zegar
	sf::Clock clock;
	/// Eventy
	sf::Event event;
	/// Tytul okna
	std::string title;
	/// Stos wskaznikow na stany
	std::stack<Stan*> stos;

	//Testy

	/**
	 * @brief Sluzy do wczytania/stworzenia testowanych obiektow
	 *
	 */
	void testyWczytaj() {
		//this->testObrazu = new Obiekt("Obraz.jpg", sf::Vector2f(50, 50));
		addStan();
	}


	/**
	 * @brief Funkcja do odpalania/renderowania testowanych obiektow
	 *
	 */
	void testyRun() {
		//this->window->draw(this->testObrazu->sprajt);
	}


	/**
	 * @brief Prywatny konstruktor, tworzy obiekt Engine
	 *
	 * @param title Tytul okna
	 * @param window_width Szerokosc okna
	 * @param window_height Wysokosc okna
	 */
	Engine(std::string title, float window_width, float window_height) {
		this->title = title;
		this->window_width = window_width;
		this->window_height = window_height;

		makeWindow();
		testyWczytaj();

	}


	/**
	 * @brief Tworzy nowe okno
	 *
	 */
	void makeWindow() {
		if (window_width && window_height) {
			this->window = new sf::RenderWindow(sf::VideoMode(this->window_width, this->window_height), this->title);
			this->window->setKeyRepeatEnabled(false);
		}
	}


	/**
	 * @brief Odswieza stan silnika
	 *
	 */
	void update() {
		this->dtime = this->clock.restart().asSeconds(); // Aktualizuje delte czasu

		//std::cout << 1.f / dtime << std::endl; // Wyswietla fps'y
		if (!stos.empty()) {
			this->stos.top()->update(dtime);
		}
		while (this->window->pollEvent(event)) {
			if (this->event.type == sf::Event::Closed) {
				this->window->close();
			}
		}

	}


	/**
	 * @brief Funkcja rysujaca obiekty ktore znajduja sie w elemencie na szczycie stos
	 *
	 */
	void draw() {
		if (!stos.empty()) {
			this->stos.top()->draw();
		}
		window->display();
		window->clear(sf::Color::Black);
	}

	/**
	 * @brief Dodaje nowy stan na stos
	 *
	 */
	void addStan() {
		this->stos.push(new MenuGlowne(this->window, &this->stos, &this->event));
	}

public:

	/**
	 * @brief Stworzenie singletonu silnika
	 *
	 * @param title Tytul okna
	 * @param window_width Szerokosc okna
	 * @param window_height Wysokosc okna
	 * @return Engine*
	 */
	static Engine* MakeEngine(std::string title, float window_width, float window_height) {
		static Engine instance(title, window_width, window_height);
		return &instance;
	}

	/**
	 * @brief Niszczy obiekt Engine oraz jego wszystkie wskazniki
	 *
	 */
	~Engine() {
		delete(this->window);
		while (!this->stos.empty())
		{
			delete this->stos.top();
			this->stos.pop();
		}
	}


	/**
	 * @brief Funkcja uruchamiajaca program
	 *
	 */
	void start() {
		while (this->window->isOpen()) {
			testyRun();
			update();
			draw();
		}
		// Tutaj trzeba dac usówanie zeby nie bylo wycieku pamieci z Gra.h
	}


	/**
	 * @brief Ustawia wymiary okna
	 *
	 * @param window_width Szerokosc
	 * @param window_height Wysokosc
	 */
	void setResolution(float window_width, float window_height) { /// Ustawienie rozmiaru okna
		this->window_width = window_width;
		this->window_height = window_height;
		window->setSize(sf::Vector2u(this->window_width, this->window_height));
	}


	/**
	 * @brief Ustawia pelny obraz
	 *
	 */
	void setFullScreen() {/// Ustawia pelny ekran
		window->create(sf::VideoMode::getDesktopMode(), "Borderless Fullscreen", sf::Style::None);
	}


	/**
	 * @brief Ustawia limit wyswietlanych klatek
	 *
	 * @param l Ilosc klatek
	 */
	void setFrameRateCap(unsigned int l) { /// Ustawia limit klatek na sekunde
		window->setFramerateLimit(l);
	}

};


