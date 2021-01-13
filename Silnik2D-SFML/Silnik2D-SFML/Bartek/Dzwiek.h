#pragma once
#include <vector>
#include <SFML/Audio.hpp>
#include <iostream>

/**
 * @brief Klasa reprezentujaca dzwiek
 *
 */
class Dzwiek
{
	/// buffor dzwieku
	sf::SoundBuffer buffer;
	/// Probka dzwieku
	sf::Sound sound;
	/// Glosnosc
	int volume;
	/// Flaga sygnalizuje czy dzwiek jest aktualnie sciszany
	bool sciszany = false;
	/// Flaga sygnalizuje czy dzwiek jest aktualnie przyglaszany
	bool przyglaszany = false;

public:

	/**
	 * @brief Konstruktor dzwieku
	 *
	 * @param sciezka Sciezka do dzwieku
	 * @param volume Glosnosc dziweku
	 */
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

	/**
	* @brief Funkcja stratujaca dzwiek
	*/
	void graj() {
		this->sound.setVolume(this->volume);
		this->sound.play();
	}

	/**
	* @brief Funkcja stopujaca dzwiek
	*/
	void stop(bool force = false) {
		if (force) this->sound.stop();
		else this->sciszany = true;
	}

	/**
	* @brief Funkcja uaktualniajaca stan dzwieku, np scisza go lub przyglasza
	*/
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

