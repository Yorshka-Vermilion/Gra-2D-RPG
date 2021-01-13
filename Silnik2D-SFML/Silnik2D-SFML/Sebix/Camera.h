#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

/**
* @brief Klasa camera odpowiadajaca za obserwowanie gracza
*/
class Camera {
	/// <summary>
	/// Widok ustawiony na gracza
	/// </summary>
	sf::View cameraPlayer;
public:
	/**
	 * @brief Konstruktor tworzenia kamery
	 *
	 * @param size Wektor liczb zmiennoprzecinkowych reprezentuj¹cych wielkoœæ kamery
	 * @param zoom Liczba zmiennoprzecinkowe reprezentuj¹ca zbli¿enie kamery
	 */
	Camera(sf::Vector2f size, double zoom) {
		this->cameraPlayer.setSize(size);
		this->cameraPlayer.zoom(zoom);
	}
	/**
	 * @brief Funkcja zwracajaca aktualny widok kamery
	 * @return View zwraca widok aktualnej kamery
	 */
	sf::View returnView() {
		return this->cameraPlayer;
	}

	/**
	 * @brief Funkcja aktualizujaca camere na podstawie pozycji gracza
	 *
	 * @param gracz Wskaznik na gracza reprezentujacy gracza ktorego ma obserwowac kamera
	 */
	void update(Gracz *gracz) {
		this->cameraPlayer.setCenter(gracz->pobierzPozycje());
		//std::cout << gracz->pobierzPozycje().x << " " << gracz->pobierzPozycje().y << std::endl;
	}
};