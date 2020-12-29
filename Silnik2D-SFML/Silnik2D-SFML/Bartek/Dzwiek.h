#pragma once
#include <vector>
#include <SFML/Audio.hpp>
#include <iostream>

class Dzwiek
{
	sf::SoundBuffer buffer;
	sf::Sound sound;
public:
	Dzwiek(std::string sciezka) {
		if (!buffer.loadFromFile(sciezka)) {
			std::cout << "Nie udalo sie zaladowac dzwieku: " << sciezka << std::endl;
		}
		else {
			sound.setBuffer(buffer);
			sound.setVolume(10);
		}
	}

	void graj() {
		this->sound.play();
	}

	void stop() {
		this->sound.stop();
	}
};

