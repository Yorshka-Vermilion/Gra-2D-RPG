#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>


class Obiekt
{
protected:
	sf::Texture tekstura; /// Zmienna przechowujaca teksture
public:
	sf::Sprite sprajt; /// Zmienna przechowujaca sprite
	Obiekt(std::string sciezka, sf::Vector2f pozycja) {
		if (!tekstura.loadFromFile(sciezka)) {
			std::cout << "Problem z zaladowaniem tekstury : " << sciezka << std::endl;
		}
		this->sprajt.setTexture(this->tekstura);
		this->sprajt.setPosition(pozycja);
	}
	void zmienTeksture(std::string sciezka) { /// Zmiana tekstury obiektu
		if (!tekstura.loadFromFile(sciezka)) {
			std::cout << "Problem z zaladowaniem tekstury : " << sciezka << std::endl;
		}
		this->sprajt.setTexture(this->tekstura);
	}

	void przestaw(sf::Vector2f gdzie) { /// Funkcja przestawiaj¹ca sprite
		this->sprajt.setPosition(gdzie);
	}

	void rotuj(float kat) { /// Funkcja obracajaca
		this->sprajt.setRotation(kat);
	}

	void przeskaluj(sf::Vector2f jak) { /// Funkcja skalujaca
		this->sprajt.setScale(jak);
	}



};

