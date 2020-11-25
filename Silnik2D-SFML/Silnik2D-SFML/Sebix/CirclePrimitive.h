#pragma once
#include <SFML\Graphics.hpp>
#include "Point2D.h"
#include "Funkcje.h"
/**
 * @brief 
 * Stala opisujaca wartosc liczby PI
 */
#define M_PI 3.14159265358979323846

/**
 * @brief 
 * Klasa opisująca okrag tworzony poprzez cztero oraz osmiokrotna symetrie
 */
class CirclePrimitive {
	/// Punkty klasy Point2D odpowiadajacy za wspolrzedne srodka okregu
	Point2D S;
	/// Liczba typu zmiennoprzecinkowego odpowiadajaca za dlugosc promienia okregu
	float R;
public:
	/**
	 * @brief Konstruktor domyslny tworzacy pusty obiekt
	 * 
	 */
	CirclePrimitive() {};
	/**
	 * @brief Konstruktor tworzacy nowy obiekt okregu
	 * 
	 * @param S Pozycja punktu srodka okregu
	 * @param R Dlugosc promienia okregu
	 */
	CirclePrimitive(Point2D S, float R) {
		this->S = S;
		this->R = R;
	}

	/**
	 * @brief Metoda odpowiedzialna za zwrocenie Point2D srodka okregu
	 * 
	 * @return Point2D - Punkt srodka okregu
	 */
	Point2D getS() {
		return this->S;
	}

	/**
	 * @brief Metoda odpowiedzialna za zwrocenie wartosci promienia okregu
	 * 
	 * @return float - Wartosc promienia okregu
	 */
	float getR() {
		return this->R;
	}

	/**
	 * @brief Metoda odpowiedzialna za ustawienie nowej wartosci srodka okregu na podstawie przekazanego parametru
	 * 
	 * @param S Point2D, który ma zostac nowym srodkiem okregu
	 */
	void setS(Point2D S) {
		this->S = S;
	}

	/**
	 * @brief Metoda odpowiedzialna za ustawienie nowej wartosci srodka okregu na podstawie przekazanego parametru
	 * 
	 * @param x Wartosc x nowego srodka okregu
	 * @param y Wartosc y nowego srodka okregu
	 */
	void setS(float x, float y) {
		this->S.position.x = x;
		this->S.position.y = y;
	}

	/**
	 * @brief Metoda odpowiedzialna za rysowanie okregu metoda czterokrotnej symetrii na podstawie pol obiektu
	 * 
	 * @param target Obiekt typu RenderTarget dla ktorego ma zostac narysowany okrag
	 */
	void drawFourCircle(sf::RenderTarget* target = nullptr) {
		int x, y; 
		for (float i = 0; i < (M_PI / 2.0); i += (1.0 / this->R)) {
			x = (this->R * cos(i)) + 0.5;
			y = (this->R * sin(i)) + 0.5;
			draw2DPoint(Point2D(sf::Vector2f(this->S.getX() +  x, this->S.getY() + y), this->S.color), target);
			draw2DPoint(Point2D(sf::Vector2f(this->S.getX() - x, this->S.getY() + y), this->S.color), target);
			draw2DPoint(Point2D(sf::Vector2f(this->S.getX() + x, this->S.getY() - y), this->S.color), target);
			draw2DPoint(Point2D(sf::Vector2f(this->S.getX() - x, this->S.getY() - y), this->S.color), target);
		};
	};
	/**
	 * @brief Metoda odpowiedzialna za rysowanie okregu metoda osmiokrotnej symetrii na podstawie pol obiektu
	 * 
	 * @param target Obiekt typu RenderTarget dla ktorego ma zostac narysowany okrag
	 */
		void drawEightCircle(sf::RenderTarget * target = nullptr) {
			int x, y;
			for (float i = 0; i < (M_PI / 4.0); i += (1.0 / this->R)) {
				x = (this->R * cos(i)) + 0.5;
				y = (this->R * sin(i)) + 0.5;
				draw2DPoint(Point2D(sf::Vector2f(this->S.getX() + x, this->S.getY() + y), this->S.color), target);
				draw2DPoint(Point2D(sf::Vector2f(this->S.getX() - x, this->S.getY() + y), this->S.color), target);
				draw2DPoint(Point2D(sf::Vector2f(this->S.getX() + x, this->S.getY() - y), this->S.color), target);
				draw2DPoint(Point2D(sf::Vector2f(this->S.getX() - x, this->S.getY() - y), this->S.color), target);
				draw2DPoint(Point2D(sf::Vector2f(this->S.getX() + y, this->S.getY() + x), this->S.color), target);
				draw2DPoint(Point2D(sf::Vector2f(this->S.getX() - y, this->S.getY() + x), this->S.color), target);
				draw2DPoint(Point2D(sf::Vector2f(this->S.getX() + y, this->S.getY() - x), this->S.color), target);
				draw2DPoint(Point2D(sf::Vector2f(this->S.getX() - y, this->S.getY() - x), this->S.color), target);
			};
		};
};


