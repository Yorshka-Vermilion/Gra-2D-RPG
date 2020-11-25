#pragma once
#include <stack>
class Stan 
{
protected:
	std::stack<Stan*>* stos; /// Stos ze stanami
	float dtime; /// Zmiana czasu
	sf::RenderWindow* window; /// Okno
	sf::Event* event; /// Wskaznik na eventy
	sf::Vector2i pozycja_kursora_w_oknie; /// Pozycja kursora w oknie
	sf::Vector2f pozycja_kursora_w_grze; /// Pozycja kursora w grze
	bool lewy = false, prawy = false; /// Stan przycisku myszy


public:
	/**
	* @brief Tworzy nowy Stan
	* 
	* @param window Wskaznik na okno
	* @param stos Wskaznik na stos z obiektami typu Stan
	* @param event Eventy
	*/
	Stan(sf::RenderWindow* window, std::stack<Stan*>* stos, sf::Event* event) {
		this->window = window;
		this->stos = stos;
		this->dtime = 0;
		this->event = event;
	}

	/**
	 * @brief Wirtualna funkcja sluzaca do odsiwezania stanu obiektu typu Stan
	 * 
	 * @param dtime Kontrola czasu
	 */
	virtual void update(const float &dtime) = 0;
	/**
	 * @brief Wirtualna funkcja rysujaca
	 * 
	 * @param cel Wskaznik na obiekt RenderTarget w ktorym rysowane sa obiekty
	 */
	virtual void draw(sf::RenderTarget* cel = nullptr) = 0;

	/**
	 * @brief Sprawdza pozycje myszy oraz zapewnia, ze nacisniecie (przytrzymanie) klawisza myszy spowoduje jedna akcje zamiast, wielu
	 * 
	 */
	void sprawdzMysz() {
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

