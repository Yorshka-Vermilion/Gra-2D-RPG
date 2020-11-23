#pragma once
#include "Animacja.h"
#include "../Sebix.h"
#include "Gracz.h"
#include "ObslugaRuchuGracza.h"

class MenuGlowne : public Stan
{
	//Obiekt* testObrazu;
	//Animacja* testAnimacji;
	Gracz* gracz; // Wskaznik na obiekt gracza
	ObslugaRuchuGracza* gRuch; // Wskaznik na obsluge ruchu gracza

	void testyWczytaj() { /// Wczytuje testowane obiekty
		//this->testObrazu = new Obiekt("Obraz.jpg", sf::Vector2f(50, 50));
		//this->testAnimacji = new Animacja("testanimacja.png", 10, 10, 765, 540, 32, 0.1);
		//this->testAnimacji->WyczyscBitmape(); // Dziala
		this->gracz = new Gracz("Postac.png", sf::Vector2f(100, 100), sf::RectangleShape(sf::Vector2f(79, 63)));
		this->gRuch = new ObslugaRuchuGracza(gracz,0.0005);
	}

	void testyRun(sf::RenderTarget* target) {/// funkcja do testowaniaa
		//target->draw(this->testObrazu->sprajt);
		this->gracz->draw(target);
	}

public:

	MenuGlowne(sf::RenderWindow* window, std::stack<Stan*>* stos, sf::Event* event) : Stan(window, stos, event) {
		testyWczytaj();
	}
	void draw(sf::RenderTarget* target) { /// Rysowanie obiektow na ekranie
		if (!target) target = this->window;
		//target->draw(...);
		//testAnimacji->animuj(target, this->dtime);
		
		testyRun(target);
	};
	void update(const float& dtime) { /// Odswiezenie stanu aktualnego "stanu"
		this->dtime = dtime;
		sprawdzMysz();
		gRuch->update(dtime);
	};
};

