#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Sebix/Point2D.h"


/**
* @brief klasa boundingbox bedaca prostokatem okalajacym
*/
class BoundingBox {
public:
	///wektor od ktorego zaczyna sie przekatna pierwszego prostokata
	Point2D d0;
	///wektor na ktorym konczy sie przekatna pierwszego prostokata
	Point2D d1;
	///wektor od ktorego zaczyna sie przekatna drugiego prostokata
	Point2D d2;
	///wektor na ktorym konczy sie przekatna drugiego prostokata
	Point2D d3;

	/**
	* @brief konstruktor domyslny klasy boundingbox
	* @param v2f przechowuje pozycje wektorow
	*/
	BoundingBox(std::vector<Point2D> v2f) {
		d0 = v2f[0];
		d1 = v2f[1];
		d2 = v2f[2];
		d3 = v2f[3];
	}

	/**
	* @brief konstruktor domyslny klasy boundingbox
	*/
	BoundingBox() {};

	void kolizja() {
		if (d0.getX() >= d2.getX()) {
			if (d0.getX() > d3.getX() && d1.getX() > d3.getX()) {
				std::cout << "__brak kolizji__";
			}
			else {
				if (d3.getY() < d0.getY() && d3.getY() < d1.getY() || d2.getY() > d0.getY() && d2.getY() > d1.getY()) {
					std::cout << "__brak kolizji__";
				}
				else {
					std::cout << "__Kolizja__";
				}
			}
		}
		else if (d0.getX() < d2.getX()) {
			if (d0.getX() < d2.getX() && d1.getX() < d2.getX()) {
				std::cout << "__brak kolizji__";
			}
			else {
				if (d3.getY() < d0.getY() && d3.getY() < d1.getY() || d2.getY() > d0.getY() && d2.getY() > d1.getY()) {
					std::cout << "__brak kolizji__";
				}
				else {
					std::cout << "__Kolizja__";
				}
			}
		}
	}
};
