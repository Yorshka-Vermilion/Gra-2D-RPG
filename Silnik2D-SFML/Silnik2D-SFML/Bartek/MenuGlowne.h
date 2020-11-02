#pragma once
#include "Bartek/Animacja.h"

class MenuGlowne : public Stan
{
	Obiekt* testObrazu;
	Animacja* testAnimacji;

	void testyWczytaj() {
		this->testObrazu = new Obiekt("Obraz.jpg", sf::Vector2f(50, 50));
		this->testAnimacji = new Animacja("testanimacja.png", 10, 10, 765, 540, 32, 0.1);
	}

	void testyRun(sf::RenderTarget* target) {// funkcja do testowaniaa
		//target->draw(this->testObrazu->sprajt);
	}

public:

	MenuGlowne(sf::RenderWindow* window, std::stack<Stan*>* stos, sf::Event* event) : Stan(window, stos, event) {
		testyWczytaj();
	}
	void draw(sf::RenderTarget* target) {
		if (!target) target = this->window;
		//target->draw(...);
		//wykonaj(10,10,150,150,this->window);
		testAnimacji->animuj(target, this->dtime);
		testyRun(target);
	};
	void update(const float& dtime) {
		this->dtime = dtime;
		sprawdzMysz();
	};
};

