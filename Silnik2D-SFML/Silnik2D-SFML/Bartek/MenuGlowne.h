#pragma once
class MenuGlowne : public Stan
{
	Obiekt* testObrazu;

	void testyWczytaj() {
		this->testObrazu = new Obiekt("Obraz.jpg", sf::Vector2f(50, 50));
	}

	void testyRun(sf::RenderTarget* target) {// funkcja do testowania
		target->draw(this->testObrazu->sprajt);
	}

public:

	MenuGlowne(sf::RenderWindow* window, std::stack<Stan*>* stos) : Stan(window, stos) {
		testyWczytaj();
	}
	void draw(sf::RenderTarget* target) {
		if (!target) target = this->window;
		//target->draw(...);
		testyRun(target);
	};
	void update(const float& dtime) {
		this->dtime = dtime;
	};
};

