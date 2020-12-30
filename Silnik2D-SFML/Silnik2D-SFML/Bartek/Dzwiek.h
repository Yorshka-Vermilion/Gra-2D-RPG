#pragma once
#include <vector>
#include <SFML/Audio.hpp>
#include <iostream>

class Dzwiek
{
	sf::SoundBuffer buffer;
	sf::Sound sound;
	int volume;
	bool sciszany = false, przyglaszany = false;
public:
	Dzwiek(std::string sciezka, int volume = 10) {
		if (!buffer.loadFromFile(sciezka)) {
			std::cout << "Nie udalo sie zaladowac dzwieku: " << sciezka << std::endl;
		}
		else {
			this->volume = volume;
			sound.setBuffer(buffer);
			sound.setVolume(this->volume);
		}
	}

	void graj() {
		this->sound.setVolume(this->volume);
		this->sound.play();
	}

	void stop(bool force = false) {
		if (force) this->sound.stop();
		else this->sciszany = true;
	}

	void update() {
		if (this->sciszany == true) {

			if (this->sound.getVolume() <= 1) {
				this->sound.setVolume(0);
				this->sound.stop();
				this->sciszany = false;
			}
			else {
				this->sound.setVolume(this->sound.getVolume() - 0.1);
			}
		}
	}
};

