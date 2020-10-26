#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stack>

class Engine
{
private:
	float window_width, window_height;
	sf::RenderWindow *window;
	std::string title;

	void makeWindow() {
		if (window_width && window_height) {
			this->window = new sf::RenderWindow(sf::VideoMode(this->window_width, this->window_height), this->title);
		}
	}
	
	Engine(std::string title, float window_width, float window_height) {
		this->window_width = window_width;
		this->window_height = window_height;
		makeWindow();
	}

public:

	static Engine* MakeEngine(std::string title, float window_width, float window_height) {
		
		static Engine instance(title,window_width,window_height);
		
		return &instance;
	}
	
	

	void start() {
		while (this->window->isOpen()) {
			sf::Event event;
			while (this->window->pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					this->window->close();
				}
			}
			
			window->clear(sf::Color::Magenta);


			window->display();
		}
	}
};


