#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>

class Engine
{
private:
	float window_width, window_height; // Wymiary okna
	float dtime; // Zmienna u¿ywana do kontroli czasu
	sf::RenderWindow *window; // Okno
	sf::Clock clock; // Zegar
	sf::Event event; // Eventy
	std::string title; // Tytu³ okna

	void makeWindow() { // Tworzy okno 
		if (window_width && window_height) {
			this->window = new sf::RenderWindow(sf::VideoMode(this->window_width, this->window_height), this->title);
		}
	}
	
	Engine(std::string title, float window_width, float window_height) { // Konstruktor prywatny
		this->window_width = window_width;
		this->window_height = window_height;
		makeWindow();
	}

public:

	static Engine* MakeEngine(std::string title, float window_width, float window_height) { // Stworzenie singletonu silnika
		static Engine instance(title,window_width,window_height);
		return &instance;
	}
	
	virtual void start() { // Funkcja uruchamiaj¹ca program
		while (this->window->isOpen()) {	
			update();
			draw();	
		}
	}

	void setResolution(float window_width, float window_height) { // Ustawienie rozmiaru okna
		this->window_width = window_width;
		this->window_height = window_height;
		window->setSize(sf::Vector2u(this->window_width,this->window_height));
	}

	void setFrameRateCap(unsigned int l) { // Ustawia limit klatek na sekunde
		window->setFramerateLimit(l);
	}

	virtual void update() { // 
		this->dtime = this->clock.restart().asSeconds(); // Aktualizuje delte czasu

		while (this->window->pollEvent(event)) {
			if (this->event.type == sf::Event::Closed) {
				this->window->close();
			}
		}
	}

	virtual void draw() { // Funkcja rysuj¹ca obrazy
		window->clear(sf::Color::Magenta);
		window->display();
	}

};


