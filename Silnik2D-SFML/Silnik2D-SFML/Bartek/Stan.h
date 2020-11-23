#pragma once
#include <stack>
class Stan 
{
protected:
	std::stack<Stan*>* stos; // Stos ze stanami
	float dtime; // Zmiana czasu
	sf::RenderWindow* window; // Okno
	sf::Event* event; // Wskaznik na eventy
	sf::Vector2i pozycja_kursora_w_oknie; // Pozycja kursora w oknie
	sf::Vector2f pozycja_kursora_w_grze; // Pozycja kursora w grze
	bool lewy = false, prawy = false; // Stan przycisku myszy


public:
	Stan(sf::RenderWindow* window, std::stack<Stan*>* stos, sf::Event* event) {
		this->window = window;
		this->stos = stos;
		this->dtime = 0;
		this->event = event;
	}

	virtual void update(const float &dtime) = 0; /// Wirtualna funkcja aktualizuj¹ca stan
	virtual void draw(sf::RenderTarget* cel = nullptr) = 0; /// Wirtualna funkcja rysuj¹ca

	void sprawdzMysz() { /// Sprawdza pozycje myszy, oraz zapewnia, ¿e nacisniêcie (przytrzymanie) klawisza myszy spowodujê jednokrotn¹ akcjê, zamiast ci¹g³ej
		this->pozycja_kursora_w_oknie = sf::Mouse::getPosition(*this->window);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->lewy = true;
		}
		else this->lewy = false;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			this->prawy = true;
		}
		else this->prawy = false;
		//std::cout << pozycja_kursora_w_oknie.x << pozycja_kursora_w_oknie.y << std::endl;
	}
};

