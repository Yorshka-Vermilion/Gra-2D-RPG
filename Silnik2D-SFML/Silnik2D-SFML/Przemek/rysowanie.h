#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Sebix/Point2D.h"
#include "../Sebix/Funkcje.h"
#include "../Silnik2D-SFML/Sebix.h"
#include  "../Sebix/LineSegment.h"
#include "../Przemek.h"

/**
* @brief funkcja do rysowania lini która znajduje sie pod katem 45 stopni lub powyzej
* @param a0 zmienna odpowiedzialna za przypisanie wektora ktory jest poczatkiem rysowanej linii
* @param a1 zmienna odpowiedzialna za przypisanie wektora ktory jest koncem rysowanej linii
* @param target obiekt typu RenderTarget dla ktorego ma zostac narysowana linia
*/
void linia_powyzej45(Point2D a0, Point2D a1, sf::RenderTarget* target) {
	int x;
	float dy;
	float dx;
	float y;
	float m;

	if (a0.getX() > a1.getX()) { 
		dy = a0.getY() - a1.getY(); 		
		dx = a0.getX() - a1.getX();					

		m = dy / dx; 

			y = a1.getY();
			for (x = a1.getX(); x <= a0.getX(); x++) {
				draw2DPoint(Point2D(sf::Vector2f(x, (int)(y + 0.5)), sf::Color::Blue), target);
				y += m; 
		}
	}

	else {
		dy = a1.getY() - a0.getY();	
		dx = a1.getX() - a0.getX();	


		m = dy / dx;

			y = a0.getY();
			for (x = a0.getX(); x <= a1.getX(); x++) {
				draw2DPoint(Point2D(sf::Vector2f(x, (int)(y + 0.5)), sf::Color::Blue), target);
				y += m;
			}
	}
}


/**
* @brief funkcja do rysowania lini która znajduje sie pod katem ponizej 45 stopni
* @param a0 zmienna odpowiedzialna za przypisanie wektora ktory jest poczatkiem rysowanej linii
* @param a1 zmienna odpowiedzialna za przypisanie wektora ktory jest koncem rysowanej linii
* @param target obiekt typu RenderTarget dla ktorego ma zostac narysowana linia
*/
void linia_ponizej45(Point2D a0, Point2D a1, sf::RenderTarget * target) {
		int y;
		float dy, dx, m, x;
		

		if (a0.getY() > a1.getY()) {
			dy = a0.getY() - a1.getY(); 		
			dx = a0.getX() - a1.getX(); 

			m = dx / dy;

				x = a1.getX();
				for (y = a1.getY(); y <= a0.getY(); y++) {
					draw2DPoint(Point2D(sf::Vector2f((int)(x + 0.5), y), sf::Color::Blue), target);
					x += m;
				}
		}

		else {
			dy = a1.getY() - a0.getY();
			dx = a1.getX() - a0.getX();

			m = dx / dy;

				x = a0.getX();
				for (y = a0.getY(); y <= a1.getY(); y++) {
					draw2DPoint(Point2D(sf::Vector2f((int)(x + 0.5), y), sf::Color::Blue), target);
					x += m;
				}
		}
}

/**
* @brief funckja sprawdzajaca ktora dokladnie funkcje rysowania lini ma wywolac
* @param a0 zmienna odpowiedzialna za przypisanie wektora ktory jest poczatkiem rysowanej linii
* @param a1 zmienna odpowiedzialna za przypisanie wektora ktory jest koncem rysowanej linii
* @param target obiekt typu RenderTarget dla ktorego ma zostac narysowana linia
*/
void wykonaj(Point2D a0, Point2D a1, sf::RenderTarget *target) { 
	
	float dy, dx, m;

		dy = a1.getY() - a0.getY();
		dx = a1.getX() - a0.getX();

		m = dy / dx;

	if(m <= 1 && m >=-1){ 
		linia_powyzej45(a0, a1, target);
	}
	if (a1.getX() == a0.getX() || m > 1 || m < -1) {
		linia_ponizej45(a0, a1, target);
	}
}

/**
* @brief klasa viewport reprezentująca prostokąt obcinający
*/
class Viewport { //klasa viewport reprezentująca prostokąt obcinający
	public:
	///wektor od ktorego zaczyna sie przekatna prostokata
	Point2D b0;
	///wektor na ktorym konczy sie przekatna prostokata	
	Point2D b1; 

	/**
	* @brief konstruktor klasy viewport
	* @param v2f przechowuje pozycje wektorow
	*/
	Viewport(std::vector<Point2D> v2f) {
		b0 = v2f[0];
		b1 = v2f[1];
	}

	/**
	* @brief funkcja odpowiedzialna za zmodyfikowanie prostokata
	* @param q zmienna odpowiedzialna za przekazywanie wspolrzednych wektora
	* @param v2f przechowuje pozycje wektorow
	*/
	void zmien_wspolrzedne(Point2D q, sf::RenderTarget* target) {
		this->b0 = q;
	}

	/**
	* @brief funkcja do wyswietlenia wspolrzednych prostokata
	* @param target obiekt typu RenderTarget ktory otrzymuje wspolrzedne linii
	*/
	void wyswietl_wspolrzedne(sf::RenderTarget* target) {
		std::cout << "Polazenie 1 wektora: wartosc x: " << b0.getX() << "wartosc y: " << b0.getY();
		std::cout << "Polazenie 2 wektora: wartosc x: " << b1.getX() << "wartosc y: " << b0.getY();
		std::cout << "Polazenie 3 wektora: wartosc x: " << b1.getX() << "wartosc y: " << b1.getY();
		std::cout << "Polazenie 4 wektora: wartosc x: " << b0.getX() << "wartosc y: " << b1.getY();
	}

	/**
	* @brief funckcja rysujaca prostokat obcinajacy
	* @param target obiekt typu RenderTarget ktory otrzymuje wspolrzedne linii
	*/
	void prostokat_obcinajacy(sf::RenderTarget* target) {

		Point2D c0 = Point2D(sf::Vector2f(b1.getX(), b0.getY()), sf::Color::Blue);
		Point2D c1 = Point2D(sf::Vector2f(b0.getX(), b1.getY()), sf::Color::Blue);

		wykonaj(b0, c0, target);
		wykonaj(c0, b1, target);
		wykonaj(b1, c1, target);
		wykonaj(c1, b0, target);
	}

};

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
	* @briefkonstruktor klasy boundingbox
	* @param v2f przechowuje pozycje wektorow
	*/
	BoundingBox(std::vector<Point2D> v2f) {
		d0 = v2f[0];
		d1 = v2f[1];
		d2 = v2f[2];
		d3 = v2f[3];
	}

	/**
	* @brief funkcja odpowiedzialna za zmodyfikowanie prostokata
	* @param w zmienna odpowiedzialna za przekazywanie wspolrzednych wektora
	* @param v2f przechowuje pozycje wektorow
	*/
	void zmien_wspolrzedne(Point2D w, sf::RenderTarget* target) {
		this->d0 = w;
	}

	/**
	* @brief funkcja do wyswietlenia wspolrzednych prostokata
	* @param target obiekt typu RenderTarget ktory otrzymuje wspolrzedne linii
	*/
	void wyswietl_wspolrzedne(sf::RenderTarget* target) {
		std::cout << "Polazenie 1 wektora z pierwszego prostokata, wartosc x: " << d0.getX() << " ,wartosc y: " << d0.getY();
		std::cout << "Polazenie 2 wektora z pierwszego prostokata, wartosc x: " << d1.getX() << " ,wartosc y: " << d0.getY();
		std::cout << "Polazenie 3 wektora z pierwszego prostokata, wartosc x: " << d1.getX() << " ,wartosc y: " << d1.getY();
		std::cout << "Polazenie 4 wektora z pierwszego prostokata, wartosc x: " << d0.getX() << " ,wartosc y: " << d1.getY();

		std::cout << "Polazenie 1 wektora z drugiego prostokata, wartosc x: " << d2.getX() << " ,wartosc y: " << d2.getY();
		std::cout << "Polazenie 2 wektora z drugiego prostokata, wartosc x: " << d3.getX() << " ,wartosc y: " << d2.getY();
		std::cout << "Polazenie 3 wektora z drugiego prostokata, wartosc x: " << d3.getX() << " ,wartosc y: " << d3.getY();
		std::cout << "Polazenie 4 wektora z drugiego prostokata, wartosc x: " << d2.getX() << " ,wartosc y: " << d3.getY();
	}

	/**
	* @brief funckcja rysujaca pierwszy prostokat 
	* @param target obiekt typu RenderTarget ktory otrzymuje wspolrzedne linii
	*/
	void prostokat_obcinajacy(sf::RenderTarget* target) {
		Point2D e0 = Point2D(sf::Vector2f(d1.getX(), d0.getY()), sf::Color::Blue);
		Point2D e1 = Point2D(sf::Vector2f(d0.getX(), d1.getY()), sf::Color::Blue);

		wykonaj(d0, e0, target);
		wykonaj(e0, d1, target);
		wykonaj(d1, e1, target);
		wykonaj(e1, d0, target);
	}

	/**
	* @brief funckcja rysujaca drugi prostokat 
	* @param target obiekt typu RenderTarget ktory otrzymuje wspolrzedne linii
	*/
	void prostokat_obcinajacy_2(sf::RenderTarget* target) { 
		Point2D e2 = Point2D(sf::Vector2f(d3.getX(), d2.getY()), sf::Color::Blue);
		Point2D e3 = Point2D(sf::Vector2f(d2.getX(), d3.getY()), sf::Color::Blue);

		wykonaj(d2, e2, target);
		wykonaj(e2, d3, target);
		wykonaj(d3, e3, target);
		wykonaj(e3, d2, target);
	}
	
	/**
	* @brief funckcja sprawdzajaca czy wystapily kolizje 
	* @param target obiekt typu RenderTarget ktory otrzymuje wspolrzedne linii
	*/
	void kolizja(sf::RenderTarget* target) {
		if (d0.getX() >= d2.getX()) {
			if (d0.getX() < d2.getX() && d1.getX() < d2.getX() || d0.getX() > d3.getX() && d1.getX() > d3.getX()) {
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
			if (d0.getX() > d2.getX() && d1.getX() > d2.getX() || d0.getX() < d3.getX() && d1.getX() < d3.getX()) {
				std::cout << "__brak kolizji__";
			}
			else {
				if (d3.getY() > d0.getY() && d3.getY() > d1.getY() || d2.getY() < d0.getY() && d2.getY() < d1.getY()) {
					std::cout << "__brak kolizji__";
				}
				else {
					std::cout << "__Kolizja__";
				}
			}
		}
	}
};
