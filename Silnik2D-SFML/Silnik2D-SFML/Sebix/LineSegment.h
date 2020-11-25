#pragma once
#include <SFML\Graphics.hpp>
#include "Point2D.h"

/**
 * @brief Klasa reprezentujaca odcinek 
 * 
 */
class LineSegment {
public:
	///Punkt reprezentujacy miejsce startowe odcinka
	Point2D start;
	///Punkt reprezentujacy miejsce koncowe odcinka
	Point2D end;
	/**
	 * @brief Konstruktor domyslny przyjmujacy dwa obiekty typu Point2D, ktore w razie braku ich przekazania sa ustawiane na wartosci bazowe
	 * 
	 * @param s Obiekt typu Point2D reprezentujacy punkt startowy linii
	 * @param e Obiekt typu Point2D reprezentujacy punkt koncowy linii
	 */
	LineSegment(Point2D s = Point2D(sf::Vector2f(0.f, 0.f), sf::Color::Magenta), Point2D e = Point2D(sf::Vector2f(0.f, 0.f), sf::Color::Magenta)) : start(s), end(e) {}
	/**
	 * @brief Konstruktor przyjmujacy wektor wektorow zmiennoprzecinkowych oraz kolor linii
	 * 
	 * @param v2f Wektor wektorow zmiennoprzecinkowych na bazie ktorego beda przypisywane punkty poczatkowy i koncowy
	 * @param c Obiekty typu Color reprezentujacy kolor linii na ekranie
	 */
	LineSegment(std::vector<sf::Vector2f> v2f, sf::Color c){
		start = Point2D(v2f[0], c);
		end = Point2D(v2f[1], c);
	}

	/**
	 * @brief Metoda zwraca punkt startowy linii
	 * 
	 * @return Point2D - Punkt startowy 
	 */
	Point2D getStart() {
		return this->start;
	}

	/**	
	 * @brief Metoda zwraca punkt koncowy linii
	 * 
	 * @return Point2D - Punkt koncowy 
	 */
	Point2D getEnd() {
		return this->end;
	}

	/**
	 * @brief Metoda zwraca wektor punktu startowego linii
	 * 
	 * @return sf::Vector2f - Pozycja punktu startowego
	 */
	sf::Vector2f getStartVector() {
		return sf::Vector2f(this->start.position);
	}

	/**
	 * @brief Metoda zwraca wektor punktu koncowego linii
	 * 
	 * @return sf::Vector2f - Pozycja punktu koncowego
	 */
	sf::Vector2f getEndVector() {
		return sf::Vector2f(this->end.position);
	}

	/**
	 * @brief Metoda umozliwia zmiane polozenia punktu poczatkowego linii
	 * 
	 * @param start Wektor reprezentujacy nowa pozycje punktu startowego
	 */
	void setStart(sf::Vector2f start) {
		this->start.position = start;
	}

	/**
	 * @brief Metoda umozliwia zmiane pozycji punktu poczatkowego istniejacej linii
	 * 
	 * @param x Pozycja x punktu poczatkowego
	 * @param y Pozycja y punktu poczatkowego
	 */
	void setStart(float x, float y) {
		this->start.position = sf::Vector2f(x,y);
	}

	/**
	 * @brief Metoda umozliwia zmiane polozenia punktu koncowego linii
	 * 
	 * @param end Wektor reprezentujacy nowa pozycje punktu koncowego
	 */
	void setEnd(sf::Vector2f end) {
		this->end.position = end;
	}

	/**
	 * @brief Metoda umozliwia zmiane pozycji punktu koncowego istniejacej linii
	 * 
	 * @param x Pozycja x punktu koncowego
	 * @param y Pozycja y punktu koncowego
	 */
	void setEnd(float x, float y) {
		this->end.position = sf::Vector2f(x, y);
	}
};