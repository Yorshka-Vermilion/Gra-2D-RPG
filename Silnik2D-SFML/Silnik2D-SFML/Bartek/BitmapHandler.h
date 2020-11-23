#pragma once



class BitmapHandler {
	sf::Image obraz;

public:
	void stworz(unsigned int width, unsigned int height, const sf::Color& color = sf::Color(0, 0, 0)) {
		this->obraz.create(width, height, color);
	}

	void usun() {
		this->obraz.~obraz();
	}

	bool zaladuj(std::string &sciezka) {
		return this->obraz.loadFromFile(sciezka);
	}

	bool zapisz(std::string& sciezka) {
		return this->obraz.saveToFile(sciezka);
	}

};