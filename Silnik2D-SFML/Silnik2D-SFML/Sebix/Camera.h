#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Camera {
	sf::View cameraPlayer;
public:
	Camera(sf::Vector2f size, double zoom) {
		this->cameraPlayer.setSize(size);
		this->cameraPlayer.zoom(zoom);
	}

	sf::View returnView() {
		return this->cameraPlayer;
	}

	void update(Gracz *gracz) {
		this->cameraPlayer.setCenter(gracz->pobierzPozycje());
		//std::cout << gracz->pobierzPozycje().x << " " << gracz->pobierzPozycje().y << std::endl;
	}
};