#pragma once
#include "Animacja.h"
#include "../Sebix.h"
#include "Gracz.h"
#include "ObslugaRuchuGracza.h"
#include "Demo.h"

class MenuGlowne : public Stan
{
	Demo* demo;

public:

	MenuGlowne(sf::RenderWindow* window, std::stack<Stan*>* stos, sf::Event* event) : Stan(window, stos, event) {
		this->demo = new Demo(window, stos, event);
		demo->demoWczytaj();
	}
	~MenuGlowne() {
		delete(this->demo);
	}

	void draw(sf::RenderTarget* target) { /// Rysowanie obiektow na ekranie
		if (!target) target = this->window;
		demo->draw(target);
	};
	void update(const float& dtime) { /// Odswiezenie stanu aktualnego "stanu"
		this->dtime = dtime;
		sprawdzMysz();
		demo->update(dtime);
	};
};

