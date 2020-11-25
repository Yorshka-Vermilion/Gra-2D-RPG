#pragma once
#include <SFML\Graphics.hpp>
#include<array>
#include "Point2DArray.h"
#include "Point2D.h"
#include "Funkcje.h"

/**
 * @brief Klasa reprezentujaca prymityw obcinajacy
 * 
 */
class Moveport {
	///Zbior punktow wierzcholkow prymitywu obcinajacego
	Point2DArray p2da;
	///Pole reprezentujace obecnie najmniejsza wartosc pozycji x prymitywu
	float xp;
	///Pole reprezentujace obecnie najwieksza wartosc pozycji x prymitywu
	float xk;
	///Pole reprezentujace obecnie najmniejsza wartosc pozycji y prymitywu
	float yp;
	///Pole reprezentujace obecnie najwieksza wartosc pozycji x prymitywu
	float yk;
public:
	/**
	 * @brief Konstruktor domyslny reprezentujacy pusty obiekt prymitywu obcinajacego
	 * 
	 */
	Moveport() {};
	/**
	 * @brief Konstruktor definujacy wierzcholki prymitywu obcinajacego
	 * 
	 * @param p2da Obiekt typu Point2DArray, ktory ma zostac wyswietlony na ekranie. Reprezentuje zbior punktow wierzcholkow prymitywu
	 */
	Moveport(Point2DArray p2da) {
		this->p2da = p2da;
	}

	/**
	 * @brief Metoda odpowiedzialna za zwrocenie Point2D reprezentujacego pierwszy z wierzcholkow prymitywu
	 * 
	 * @return Point2D - Pierwszy wierzcholek prymitywu
	 */
	Point2D returnA() {
		return this->p2da.p2d[0];
	}
	/**
	 * @brief Metoda odpowiedzialna za zwrocenie Point2D reprezentujacego drugi z wierzcholkow prymitywu
	 * 
	 * @return Point2D - Drugi wierzcholek prymitywu
	 */
	Point2D returnB() {
		return this->p2da.p2d[1];
	}
	/**
	 * @brief Metoda odpowiedzialna za zwrocenie Point2D reprezentujacego trzeci z wierzcholkow prymitywu
	 * 
	 * @return Point2D - Trzeci wierzcholek prymitywu
	 */
	Point2D returnC() {
		return this->p2da.p2d[2];
	}
	/**
	 * @brief Metoda odpowiedzialna za zwrocenie Point2D reprezentujacego czwarty z wierzcholkow prymitywu
	 * 
	 * @return Point2D - Czwarty wierzcholek prymitywu
	 */
	Point2D returnD() {
		return this->p2da.p2d[3];
	}

	/**
	 * @brief Metoda odpowiedzialna za ustawienie nowej pozycji dla juz istniejacego pierwszego wierzcholka
	 * 
	 * @param v2f Wektor z nowa pozycja pierwszego wierzcholka
	 */
	void setA(sf::Vector2f v2f) {
		this->p2da.p2d[0].position = v2f;
	}

	/**
	 * @brief Metoda odpowiedzialna za ustawienie nowej pozycji dla juz istniejacego drugiego wierzcholka
	 * 
	 * @param v2f Wektor z nowa pozycja drugiego wierzcholka
	 */
	void setB(sf::Vector2f v2f) {
		this->p2da.p2d[1].position = v2f;
	}

	/**
	 * @brief Metoda odpowiedzialna za ustawienie nowej pozycji dla juz istniejacego trzeciego wierzcholka
	 * 
	 * @param v2f Wektor z nowa pozycja trzeciego wierzcholka
	 */
	void setC(sf::Vector2f v2f) {
		this->p2da.p2d[2].position = v2f;
	}

	/**
	 * @brief Metoda odpowiedzialna za ustawienie nowej pozycji dla juz istniejacego czwartego wierzcholka
	 * 
	 * @param v2f Wektor z nowa pozycja czwartego wierzcholka
	 */
	void setD(sf::Vector2f v2f) {
		this->p2da.p2d[3].position = v2f;
	}

	/**
	 * @brief Metoda odpowiedzialna za narysowanie na ekranie prymitywu obcinajacego
	 * 
	 * @param target Obiekt typu RenderTarget dla ktorego ma zostac narysowany prymityw
	 */
	void drawViewport(sf::RenderTarget* target = nullptr) {
		drawLineZamknieta(this->p2da, target);
	}

	/**
	 * @brief Metoda odpowiedzialna za poruszanie prymitywem w momecie nacisniedcia klawisza
	 * 
	 */
	void moveViewport() {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
			this->setA(sf::Vector2f(this->returnA().getX(), this->returnA().getY() - 4));
			this->setB(sf::Vector2f(this->returnB().getX(), this->returnB().getY() - 4));
			this->setC(sf::Vector2f(this->returnC().getX(), this->returnC().getY() - 4));
			this->setD(sf::Vector2f(this->returnD().getX(), this->returnD().getY() - 4));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
			this->setA(sf::Vector2f(this->returnA().getX(), this->returnA().getY() + 4));
			this->setB(sf::Vector2f(this->returnB().getX(), this->returnB().getY() + 4));
			this->setC(sf::Vector2f(this->returnC().getX(), this->returnC().getY() + 4));
			this->setD(sf::Vector2f(this->returnD().getX(), this->returnD().getY() + 4));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			this->setA(sf::Vector2f(this->returnA().getX() + 4, this->returnA().getY()));
			this->setB(sf::Vector2f(this->returnB().getX() + 4, this->returnB().getY()));
			this->setC(sf::Vector2f(this->returnC().getX() + 4, this->returnC().getY()));
			this->setD(sf::Vector2f(this->returnD().getX() + 4, this->returnD().getY()));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			this->setA(sf::Vector2f(this->returnA().getX() - 4, this->returnA().getY()));
			this->setB(sf::Vector2f(this->returnB().getX() - 4, this->returnB().getY()));
			this->setC(sf::Vector2f(this->returnC().getX() - 4, this->returnC().getY()));
			this->setD(sf::Vector2f(this->returnD().getX() - 4, this->returnD().getY()));
		}
	}

	/**
	 * @brief Metoda sprawdzajaca w czasie rzeczywistym, wartosci pozycji maksymalnej i minimalnej
	 * 
	 */
	void checkXYpk() {
		std::vector<float> tmp = findXes(this->p2da.p2d);
		this->xp = tmp.back();
		tmp.pop_back();
		this->xk = tmp.back();
		tmp.pop_back();
		tmp = findYes(p2da.p2d);
		this->yp = tmp.back();
		tmp.pop_back();
		this->yk = tmp.back();
		tmp.pop_back();
	}

	/**
	 * @brief Metoda sprawdzajaca i wyswietlajaca punkt znajdujacy sie w obrebie prymitywu
	 * 
	 * @param p2d Obiekt typu Point2D, ktory ma zostac sprawdzony pod wzgledem pozycji w prymitywie
	 * @param target Obiekt typu RenderTarget dla ktorego maja zostac narysowane punkty
	 * @return true - Zostaje zwrocone w sytuacji gdy punkt znajduje sie we wnetrzu prymitywu
	 * @return false - Zostaje zwrocone w sytuacji gdy punkt znajduje sie poza polem prymitywu
	 */
	bool cutViewportPoint(Point2D p2d, sf::RenderTarget* target = nullptr) {
		this->checkXYpk();
		if ((xp <= p2d.getX() && p2d.getX() <= xk) && (yp <= p2d.getY() && p2d.getY() <= yk)) {
			draw2DPoint(p2d, target);
			return true;
		}
		return false;
	}

	/**
	 * @brief Metoda obliczajaca pozycje bitowa punktu dla algorytmu Cohen sutherland
	 * 
	 * @param p2d Obiekt typu Point2D reprezentujacy punkt
	 * @return std::array<int, 4> - Zwrocona zostaje tablica zawierajaca reprezentacje bitowa punktu
	 */
	std::array<int, 4> bitCheck(Point2D p2d) {
		std::array<int, 4> tab = { 0, 0, 0, 0 };
		if (p2d.getY() < this->yp) tab[3] = 1;
		else if (p2d.getY() > this->yk) tab[2] = 1;
		if (p2d.getX() > this->xk) tab[1] = 1;
		else if (p2d.getX() < this->xp) tab[0] = 1;
		return tab;
	}


	/**
	 * @brief Metoda odpowiedzialna za przycinanie linii po przez prymityw z wykorzystaniem algorytmu Cohen sutherland
	 * 
	 * @param ls Obiekt typu LineSegment reprezentujacy linie na ekranie
	 * @param target Obiekt typu RenderTarget dla ktorego ma zostac narysowana linia
	 * @return LineSegment - Zwrocony zostaje fragment lini, zaleznie od efektu metody
	 */
	LineSegment cutViewportLine(LineSegment ls, sf::RenderTarget* target = nullptr) {
		this->checkXYpk();
		while(true){
			std::array<int, 4> StartT = this->bitCheck(ls.getStart());
			std::array<int, 4> EndT = this->bitCheck(ls.getEnd());
			int Start = (StartT[0] + StartT[1] * 2 + StartT[2] * 4 + StartT[3] * 8);
			int End = (EndT[0] + EndT[1] * 2 + EndT[2] * 4 + EndT[3] * 8);
			int Check = ((StartT[0] && EndT[0]) + (StartT[1] && EndT[1]) * 2 + (StartT[2] && EndT[2]) * 4 + (StartT[3] && EndT[3])*8);
			if (Start == 0 && End == 0) {
				draw2DLine(ls.getStart(),ls.getEnd(),target);
				return ls;
			}
			else if(Check != 0) {
				return LineSegment();
			}
			else {
				if (Start == 0) {
					sf::Vector2f tmp = ls.getStart().position;
					ls.setStart(ls.getEnd().position);
					ls.setEnd(tmp);

					StartT = this->bitCheck(ls.getStart());
					EndT = this->bitCheck(ls.getEnd());
				}
				if (StartT[0] == 1) {
					int tmpx = ls.getEnd().getX();
					int tmpy = ls.getEnd().getY();
					ls.start.position.y = ls.start.position.y + (xp - ls.start.position.x) * (ls.end.position.y - ls.start.position.y) / (ls.end.position.x - ls.start.position.x);
					ls.start.position.x = xp;
				}
				if (StartT[1] == 1) {
					int tmpx = ls.getEnd().getX();
					int tmpy = ls.getEnd().getY();
					ls.start.position.y = ls.start.position.y + (xk - ls.start.position.x) * (ls.end.position.y - ls.start.position.y) / (ls.end.position.x - ls.start.position.x);
					ls.start.position.x = xk;
				}
				if (StartT[2] == 1) {
					int tmpx = ls.getEnd().getX();
					int tmpy = ls.getEnd().getY();
					ls.start.position.x = ls.start.position.x + (yk - ls.start.position.y) * (ls.end.position.x - ls.start.position.x) / (ls.end.position.y - ls.start.position.y);
					ls.start.position.y = yk;
				}
				if (StartT[3] == 1) {
					int tmpx = ls.getEnd().getX();
					int tmpy = ls.getEnd().getY();
					ls.start.position.x = ls.start.position.x + (yp - ls.start.position.y) * (ls.end.position.x - ls.start.position.x) / (ls.end.position.y - ls.start.position.y);
					ls.start.position.y = yp;
				}
			}
		}
	}

	/**
	 * @brief Metoda odpowiedzialna za obcinanie zbioru linii
	 * 
	 * @param lss Wektor obiektow typu LineSegment, zawierajacych roznego rodzaju odcinki
	 * @param target Obiekt typu RenderTarget dla ktorego maja zostac narysowane linie
	 */
	void cutViewportLines(std::vector<LineSegment> lss, sf::RenderTarget* target = nullptr) {
		for (int i = 0; i < lss.size(); i++) {
			cutViewportLine(lss[i], target);
		}
	}

	
};
