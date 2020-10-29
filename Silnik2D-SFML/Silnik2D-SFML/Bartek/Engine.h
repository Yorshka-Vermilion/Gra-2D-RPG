#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>
#include "../Sebix.h"
#include "../Bartek.h"

class Engine
{
private:
	float window_width, window_height; // Wymiary okna
	float dtime; // Zmienna u¿ywana do kontroli czasu
	sf::RenderWindow *window; // Okno
	sf::Clock clock; // Zegar
	sf::Event event; // Eventy
	std::string title; // Tytu³ okna
	std::stack<Stan*> stos; //Stos wska¿ników a stany

	//Testy
	

	void testyWczytaj() {
		//this->testObrazu = new Obiekt("Obraz.jpg", sf::Vector2f(50, 50));
		addStan();
	}

	void testyRun() {// funkcja do testowania
		//this->window->draw(this->testObrazu->sprajt);
	}

	
	Engine(std::string title, float window_width, float window_height) { // Konstruktor prywatny
		this->title = title;
		this->window_width = window_width;
		this->window_height = window_height;
		makeWindow();
		testyWczytaj();
	}

	void makeWindow() { // Tworzy okno 
		if (window_width && window_height) {
			this->window = new sf::RenderWindow(sf::VideoMode(this->window_width, this->window_height), this->title);
		}
	}

	void update() { // 
		this->dtime = this->clock.restart().asSeconds(); // Aktualizuje delte czasu

		while (this->window->pollEvent(event)) {
			if (this->event.type == sf::Event::Closed) {
				this->window->close();
			}
		}
		if (!stos.empty()) {
			this->stos.top()->update(dtime);
		}
	}

	void draw() { // Funkcja rysuj¹ca obrazy
		if (!stos.empty()) {
			this->stos.top()->draw();
		}
		window->display();
		window->clear(sf::Color::Black);
	}

	void addStan() {
		this->stos.push(new MenuGlowne(this->window,&this->stos,&this->event));
	}

public:

	static Engine* MakeEngine(std::string title, float window_width, float window_height) { // Stworzenie singletonu silnika
		static Engine instance(title,window_width,window_height);
		return &instance;
	}
	
	void start() { // Funkcja uruchamiaj¹ca program
		while (this->window->isOpen()) {	
			testyRun();
			update();
			draw();	
		}
	}

	void setResolution(float window_width, float window_height) { // Ustawienie rozmiaru okna
		this->window_width = window_width;
		this->window_height = window_height;
		window->setSize(sf::Vector2u(this->window_width,this->window_height));
	}

	void setFullScreen() {// Ustawia pelny ekran
		window->create(sf::VideoMode::getDesktopMode(), "Borderless Fullscreen", sf::Style::None);
	}

	void setFrameRateCap(unsigned int l) { // Ustawia limit klatek na sekunde
		window->setFramerateLimit(l);
	}
	
};


