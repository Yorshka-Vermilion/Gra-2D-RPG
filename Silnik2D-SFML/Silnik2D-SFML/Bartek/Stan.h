#pragma once
#include <stack>
class Stan 
{
protected:
	std::stack<Stan*>* stos; // Stos ze stanami
	float dtime; // Zmiana czasu
	sf::RenderWindow* window; // Okno


public:
	Stan(sf::RenderWindow* window, std::stack<Stan*>* stos) {
		this->window = window;
		this->stos = stos;
		this->dtime = 0;
	}

	virtual void update(const float &dtime) = 0; // Wirtualna funkcja aktualizuj¹ca stan
	virtual void draw(sf::RenderTarget* cel = nullptr) = 0; // Wirtualna funkcja rysuj¹ca
};

