#pragma once
#include "Stan.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Mapa.h"
#include <iostream>


/**
 * @brief Klasa w ktorej bedzie znajdowal sie kod gry
 * 
 */
class Gra : public Stan
{
	Mapa* map;
	Obiekt* maska;
	Gracz* gracz;
	ObslugaRuchuGracza* gRuch;
	HUD* hud;
	DrzewoDialogow* drzewo;

	std::vector<Animacja*> animacje;

public:
	Gra(sf::RenderWindow* window, std::stack<Stan*>* stos, sf::Event* event) : Stan(window, stos, event) {
		this->drzewo = new DrzewoDialogow();
		this->gracz = new Gracz("Postac.png", sf::Vector2f(100, 100), sf::RectangleShape(sf::Vector2f(79, 63)),100,300,1000);
		this->gRuch = new ObslugaRuchuGracza(this->gracz, 300,this->drzewo);
		//this->hud = new HUD("gui.png", sf::Vector2f(window->getSize()), gracz);
		this->map = new Mapa(25, window->getSize());
		

		//Maska
		this->maska = new Obiekt("maska.png", sf::Vector2f(0, 0));
		this->maska->setOriginOnMiddle();
		this->maska->przestaw(sf::Vector2f(990, 540));
		this->maska->przeskaluj(sf::Vector2f(1.55, 1.15));

		//Testy
		this->animacje.push_back(new Animacja("animacja.png",350,350,32,32,12,1,true,false));
		this->animacje.push_back(new Animacja("animacja.png", 30, 350, 32, 32, 12, 0.1, true, false));
		this->animacje.push_back(new Animacja("animacja.png", 80, 350, 32, 32, 12, 0.75, true, false));
	}

	~Gra() {
		delete(this->map);
		delete(this->maska);
		delete(this->drzewo);
		delete(this->gRuch);
		delete(this->gracz);
		delete(this->hud);
		delete(this->event);
		delete(this->stos);
		delete(this->window);
	}

	void obslugaAnimacji(sf::RenderTarget* target) {
		size_t zasieg = this->animacje.size();
		for (size_t i = 0; i < zasieg; i++) {
			this->animacje.at(i)->animuj(target,this->dtime);
			if (this->animacje.at(i)->koniec()) {
				this->animacje.erase(this->animacje.begin() + i);
				i--;
				zasieg--;
			}
		}
	}

	void draw(sf::RenderTarget* target) { /// Rysowanie obiektow na ekranie
		if (!target) target = this->window;
		this->map->draw(target);
		this->gracz->draw(target);
		//this->maska->draw(target);
		//this->hud->draw(target);

		//Testy
		//this->animacje.at(0)->animuj(target,this->dtime);
		obslugaAnimacji(target);
	};

	void update(const float& dtime) { /// Odswiezenie stanu aktualnego "stanu"
		this->dtime = dtime;
		//this->hud->update();
		this->gRuch->update(dtime);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			this->map->Przesun(2);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
			this->map->Przesun(3);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
			this->map->Przesun(0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
			this->map->Przesun(1);
		}
		sprawdzMysz();
	};
};


