#pragma once


/**
 * @brief Klasa obslugujaca bitmapy
 * 
 */
class BitmapHandler {
	

public:
	sf::Image obraz; /// Przechowuje obraz

	/**
	 * @brief Tworzy nowy obraz
	 * 
	 * @param width Szerokosc obrazu
	 * @param height Wysokosc obrazu
	 * @param color Kolor wypelnienia
	 */
	void stworz(unsigned int width, unsigned int height, const sf::Color& color = sf::Color(255, 0, 0)) { /// Tworzy obraz (bitmape)
		this->obraz.create(width, height, color);
	}

	/**
	 * @brief Usowa bitmape
	 * 
	 */
	void usun() {
		this->obraz.~obraz();
	}


	/**
	 * @brief Laduje bitmape z plik
	 * 
	 * @param sciezka Sciezka do pliku
	 * @return true Jesli sie powiodlo
	 * @return false Jesli sie nie powiodlo
	 */
	bool zaladuj(std::string sciezka) {
		return this->obraz.loadFromFile(sciezka);
	}

	/**
	 * @brief Zapisuje bitmape do pliku
	 * 
	 * @param sciezka Sciezka do pliku
	 * @return true Jesli sie powiodlo
	 * @return false Jesli sie nie powiodlo
	 */
	bool zapisz(std::string sciezka) { /// Zapisuje bitmape do pliku
		return this->obraz.saveToFile(sciezka);
	}


	/**
	 * @brief Niszczy obiekt BitmapHandler
	 * 
	 */
	~BitmapHandler() {
		obraz.~Image();
	}
};