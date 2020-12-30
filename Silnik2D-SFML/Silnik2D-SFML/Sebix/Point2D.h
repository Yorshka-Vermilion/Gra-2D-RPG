#pragma once

#include <SFML/Graphics.hpp>

/**
 * @brief Klasa odpowiedzialna za reprezentacje jednego pixlela na ekranie dziedziczaca po klasie Vertex
 * 
 */
class Point2D : public sf::Vertex {

public:
	/**
	 * @brief Konstruktor wywolywany na bazie klasy Vertex
	 * 
	 * @param xy Wektor liczb zmiennoprzecinkowych reprezetujacy pozycje pixela
	 * @param color Obiekt typu Color reprezentujacy kolor pixela
	 */
	Point2D(const sf::Vector2f& xy, const sf::Color& color) : sf::Vertex(xy,color){}

	/**
	 * @brief Konstruktor wywolywany na bazie klasy Vertex bez przekazania koloru, ktory jest ustawiany na bazowy
	 * 
	 * 
	 * @param xy Wektor liczb zmiennoprzecinkowych reprezetujacy pozycje pixela
	 */
	Point2D(const sf::Vector2f& xy) : sf::Vertex(xy){
		this->color = sf::Color::Black;
	}

	/**
	 * @brief Konstruktor domyslny reprezentujacy pusty pixel
	 * 
	 */
	Point2D() {}

	/**
	 * @brief Metoda zwracajaca pozycje x pixela
	 * 
	 * @return float - Wartosc x
	 */
	float getX() {
		return this->position.x;
	}

	/**
	 * @brief Metoda zwracajaca pozycje y pixela
	 * 
	 * @return float - Wartosc y
	 */
	float getY() {
		return this->position.y;
	}
};


