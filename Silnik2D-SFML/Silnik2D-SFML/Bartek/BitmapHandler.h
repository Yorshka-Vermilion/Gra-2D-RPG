#pragma once



class BitmapHandler {
	sf::Image obraz; // Przechowuje obraz

public:
	void stworz(unsigned int width, unsigned int height, const sf::Color& color = sf::Color(0, 0, 0)) { // Tworzy obraz (bitmape)
		this->obraz.create(width, height, color);
	}

	void usun() { // Usuwa bitmape
		this->obraz.~obraz();
	}

	bool zaladuj(std::string &sciezka) { // Laduje bitmape z pliku
		return this->obraz.loadFromFile(sciezka);
	}

	bool zapisz(std::string& sciezka) { // Zapisuje bitmape do pliku
		return this->obraz.saveToFile(sciezka);
	}

};