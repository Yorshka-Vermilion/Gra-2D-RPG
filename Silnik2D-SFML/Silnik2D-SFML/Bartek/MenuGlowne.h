#pragma once
#include "Bartek/Animacja.h"
#include "../Sebix.h"

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
		//testAnimacji->animuj(target, this->dtime);

		//Rysuje pixel na ekranie
		/*
		sf::Vector2f v2f = sf::Vector2f(10.0, 10.0);
		Point2D p2d = Point2D(v2f, sf::Color::Blue);
		draw2DPoint(p2d,target);
		
		//Rysuje figure na ekranie
		
		std::vector<sf::Vector2f> vector;
		vector.push_back(sf::Vector2f(100.f, 100.f));
		vector.push_back(sf::Vector2f(10.f, 100.f));
		vector.push_back(sf::Vector2f(10.f, 10.f));
		vector.push_back(sf::Vector2f(100.f, 10.f));
		
		Point2DArray p2da = Point2DArray(vector, sf::Color::Cyan);
		draw2DEmpty(p2da, target);
		

		// Rysuje linie algorytmem przyrostowym
		std::vector<sf::Vector2f> v;
		v.push_back(sf::Vector2f(300.f, 300.f));
		v.push_back(sf::Vector2f(10.f, 10.f));
		LineSegment ls = LineSegment(v, sf::Color::Cyan);

		drawLinePrzyrostowo(ls,target);
		*/

		testyRun(target);
	};
	void update(const float& dtime) {
		this->dtime = dtime;
		sprawdzMysz();
	};
};

