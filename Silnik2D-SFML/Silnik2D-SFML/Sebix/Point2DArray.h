#pragma once
#include <SFML\Graphics.hpp>
#include "Point2D.h"

/**
 * @brief Klasa odpowiedzialna za reprezentacje zbioru pixleli na ekranie dziedziczaca po klasie VertexArray
 * 
 */
class Point2DArray : public sf::VertexArray {
public:
	///Wlasny wektor Point2D reprezentujacy zbior pixeli na ekranie
	std::vector<Point2D> p2d;
	/**
	 * @brief Konstruktor domyslny reprezentujacy pusty zbior pixeli wywolany na bazie VertexArray
	 * 
	 */
	Point2DArray() : sf::VertexArray() {}
	/**
	 * @brief Konstruktor przyjmujacy wartosc PrimitiveType oraz size_t odpowiedzialne za wielkosc oraz rodzaj zbioru
	 * 
	 * @param pt Obiekt reprezentujacy typ rysowanego prymitywu
	 * @param v Zadana wielkosc zbioru
	 */
	Point2DArray(sf::PrimitiveType pt, size_t v) : sf::VertexArray(pt, v) {}

	/**
	 * @brief Konstruktor pobierajacy wektor wektorow liczb zmiennoprzecinkowych oraz kolor do wypelnienia zbioru
	 * 
	 * @param v2f Wektor obiektow Vector2f reprezentujacych pozycje pixeli w zbiorze
	 * @param c Obiekt Color reprezentujacy kolor pixeli na ekranie
	 */
	Point2DArray(std::vector<sf::Vector2f> v2f, sf::Color c) {
		for (int i = 0; i < v2f.size(); i++) {
			p2d.push_back(Point2D(v2f[i], c));
		}
	}

	/**
	 * @brief Metoda umozliwiajaca dodanie punktu do zbioru
	 * 
	 * @param v2f Wektor posiadajacy wartosci pozycji nowego pixela
	 */
	void add2DPoint(sf::Vector2f v2f){
		p2d.push_back(Point2D(v2f, sf::Color::Black));
	}
	
};