#pragma once
#include "Stan.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Gra : public Stan
{

public:
	Gra(sf::RenderWindow* window, std::stack<Stan*>* stos, sf::Event* event) : Stan(window, stos, event) {
		
	}
};

