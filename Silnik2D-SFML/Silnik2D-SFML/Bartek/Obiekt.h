#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

//Trzeba dodaæ kszta³t (do kolizji) update tekstury (zmiana miejsca)

class Obiekt
{
protected:
	sf::Texture tekstura; // Zmienna przechowujaca teksture
public:
	sf::Sprite sprajt; // Zmienna przechowujaca sprite
	Obiekt(std::string sciezka, sf::Vector2f pozycja) {
		if (!tekstura.loadFromFile(sciezka)) {
			std::cout << "Problem z zaladowaniem tekstury : " << sciezka << std::endl;
		}
		this->sprajt.setTexture(this->tekstura);
		this->sprajt.setPosition(pozycja);
	}
	void WyczyscBitmape() { // Czyszczenie tekstury;
		tekstura.~Texture();
	}

};

