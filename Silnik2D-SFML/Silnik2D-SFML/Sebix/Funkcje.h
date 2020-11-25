#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Point2DArray.h"
#include "Point2D.h"
#include "LineSegment.h"


/**
 * @brief Funkcja odpowiedzialna za rysowanie pixela na ekranie
 * 
 * @param p2d Obiekt typu Point2D, ktory ma zostac wyswietlony na ekranie. Reprezentuje jeden pixel
 * @param target Obiekt typu RenderTarget dla ktorego ma zostac narysowany pixel
 */
void draw2DPoint(Point2D p2d, sf::RenderTarget* target = nullptr) { 
	target->draw(&p2d, 1, sf::PrimitiveType::Points);
}

/**
 * @brief Funkcja odpowiedzialna za narysowanie zbioru punktów na ekranie
 * 
 * @param p2da Obiekt typu Point2DArray, ktory ma zostać wyswietlony na ekranie. Reprezentuje zbior pixeli
 * @param target Obiekt typu RenderTarget dla ktorego ma zostac narysowany zbior pixeli
 */
void draw2DPoints(Point2DArray p2da, sf::RenderTarget* target = nullptr) { 
	target->draw(&p2da.p2d[0], p2da.p2d.size(), sf::PrimitiveType::Points);
}

/**
 * @brief Funkcja odpowiedzialna za narysowanie linii na ekranie
 * 
 * @param p2da Obiekt typu Point2DArray, ktory ma zostac wyswietlony na ekranie. Reprezentuje zbior punktow opisujacych punkt poczatkowy i koncowy linii
 * @param target Obiekt typu RenderTarget dla ktorego ma zostac narysowana linia
 */
void draw2DLine(Point2DArray p2da, sf::RenderTarget* target = nullptr) { 
	target->draw(&p2da.p2d[0], p2da.p2d.size(), sf::PrimitiveType::Lines);
}

/**
 * @brief Funkcja odpowiedzialna za narysowanie linii na ekranie
 * 
 * @param p2da Obiekt typu Point2D, ktory ma zostac wyswietlony na ekranie. Reprezentuje punkt poczatkowy linii
 * @param p2db Obiekt typu Point2D, ktory ma zostac wyswietlony na ekranie. Reprezentuje punkt koncowy linii
 * @param target Obiekt typu RenderTarget dla ktorego ma zostac narysowana linia
 */
void draw2DLine(Point2D p2da, Point2D p2db, sf::RenderTarget* target = nullptr) { 
	sf::Vertex line[]{
		p2da,p2db
	};
	target->draw(line, sizeof(line), sf::PrimitiveType::Lines);
}

/**
 * @brief Funkcja odpowiedzialna za narysowanie trojkata na ekranie
 * 
 * @param p2da Obiekt typu Point2DArray, ktory ma zostac wyswietlony na ekranie. Reprezentuje zbior punktow opisujacych wierzcholki trojkata
 * @param target Obiekt typu RenderTarget dla ktorego ma zostac narysowany trojkat
 */
void draw2DTriangle(Point2DArray p2da, sf::RenderTarget* target = nullptr) { 
	target->draw(&p2da.p2d[0], p2da.p2d.size(), sf::PrimitiveType::Triangles);
}

/**
 * @brief Funkcja odpowiedzialna za narysowanie kwadratu na ekranie
 * 
 * @param p2da Obiekt typu Point2DArray, ktory ma zostac wyswietlony na ekranie. Reprezentuje zbior punktow opisujacych wierzcholki kwadratu
 * @param target Obiekt typu RenderTarget dla ktorego ma zostac narysowany kwadrat
 */
void draw2DQuad(Point2DArray p2da, sf::RenderTarget* target = nullptr) { 
	target->draw(&p2da.p2d[0], p2da.p2d.size(), sf::PrimitiveType::Quads);
}

/**
 * @brief Funkcja odpowiedzialna za rysowanie pustych prymitywow
 * 
 * @param p2da Obiekt typu Point2DArray, ktory ma zostac wyswietlony na ekranie. Reprezentuje zbior punktow opisujacych prymityw
 * @param target Obiekt typu RenderTarget dla ktorego ma zostac narysowany prymityw
 */
void draw2DEmpty(Point2DArray p2da, sf::RenderTarget* target = nullptr) {
	if (p2da.p2d.size() > 0) {
		if (p2da.p2d.size() == 1)
			draw2DPoints(p2da, target);
		else if (p2da.p2d.size() == 2)
			draw2DLine(p2da, target);
		else {
			target->draw(&p2da.p2d[0], p2da.p2d.size(), sf::PrimitiveType::LineStrip);
			Point2D line[] = {
				Point2D(p2da.p2d[0].position, p2da.p2d[0].color),
				Point2D(p2da.p2d[p2da.p2d.size() - 1].position, p2da.p2d[p2da.p2d.size() - 1].color)
			};
			target->draw(line, 2, sf::PrimitiveType::Lines);
		}
	}
}

/**
 * @brief Funkcja odpowiedzialna za rysowania zbioru linii otwartych
 * 
 * @param p2da Obiekt typu Point2DArray, ktory ma zostac wyswietlony na ekranie. Reprezentuje zbior punktow poczatkowych i koncowych linii
 * @param target Obiekt typu RenderTarget dla ktorego maja zostac narysowane linie
 */
void drawLineOtwarta(Point2DArray p2da, sf::RenderTarget* target = nullptr) {
	LineSegment lstmp;
	for (int i = 0; i < p2da.p2d.size()-1; i++) {
		draw2DLine(p2da.p2d[i], p2da.p2d[i + 1], target);
	}
}

/**
 * @brief Funkcja odpowiedzialna za rysowania zbioru linii zamknietych
 * 
 * @param p2da Obiekt typu Point2DArray, ktory ma zostac wyswietlony na ekranie. Reprezentuje zbior punktow poczatkowych i koncowych linii
 * @param target Obiekt typu RenderTarget dla ktorego maja zostac narysowane linie
 */
void drawLineZamknieta(Point2DArray p2da, sf::RenderTarget* target = nullptr) {
	target->draw(&p2da.p2d[0], p2da.p2d.size(), sf::PrimitiveType::LineStrip);
	Point2D line[] = {
				Point2D(p2da.p2d[0].position, p2da.p2d[0].color),
				Point2D(p2da.p2d[p2da.p2d.size() - 1].position, p2da.p2d[p2da.p2d.size() - 1].color)
	};
	target->draw(line, 2, sf::PrimitiveType::Lines);
}


/**
 * @brief Funkcja odpowiedzialna za wyszukanie x maksymalnego oraz minimalnego w zbiorze punktow
 * 
 * @param p2d Wektor zawierajacy obiekty typu Point2D. Reprezentuje zbior punktow
 * @return std::vector<float> Zwraca dwuelementowy wektor zawierajacy wartosc maksymalna i minimalna ze zbioru x
 */
std::vector<float> findXes(std::vector<Point2D> p2d) {
	std::vector<float> tmp;
	float xk = p2d[0].getX();
	float xp = p2d[0].getX();

	for (int i = 0; i < p2d.size(); i++) {
		if (p2d[i].getX() > xk) xk = p2d[i].getX();
		if (p2d[i].getX() < xp) xp = p2d[i].getX();
	}

	tmp.push_back(xk);
	tmp.push_back(xp);
	return tmp;
}

/**
/**
 * @brief Funkcja odpowiedzialna za wyszukanie y maksymalnego oraz minimalnego w zbiorze punktow
 * 
 * @param p2d Wektor zawierajacy obiekty typu Point2D. Reprezentuje zbior punktow
 * @return std::vector<float> Zwraca dwuelementowy wektor zawierajacy wartosc maksymalna i minimalna ze zbioru y
 */
std::vector<float> findYes(std::vector<Point2D> p2d) {
	std::vector<float> tmp;
	float yk = p2d[0].getY();
	float yp = p2d[0].getY();

	for (int i = 0; i < p2d.size(); i++) {
		if (p2d[i].getY() > yk) yk = p2d[i].getY();
		if (p2d[i].getY() < yp) yp = p2d[i].getY();
	}

	tmp.push_back(yk);
	tmp.push_back(yp);
	return tmp;
}

/**
 * @brief Funkcja odpowiedzialna za narysowanie lini na tle okna. 
 * 
 * @param image Obiekt typu Image odpowiedzialny za ladowanie, manipulowanie oraz zapisywanie obrazow 
 * @param ls Obiekt typu LineSegment, ktory ma zostac wyswietlony na tle okna. Reprezentuje linie
 */
void drawLineBackground(sf::Image& image, LineSegment ls) {
	float dy, dx, y, m;
	sf::Vector2f v2fs = ls.getStartVector();
	sf::Vector2f v2fe = ls.getEndVector();
	dy = abs(v2fe.y - v2fs.y);
	dx = abs(v2fe.x - v2fs.x);

	if (v2fs.y < v2fe.y) y = v2fs.y;
	else y = v2fe.y;

	if (dx != 0) {
		if (dy / dx <= -1 || dy / dx >= 1) std::swap(dx, dy);
		m = dy / dx;
	}
	else m = 0;

	if (dx != 0) {
		if (v2fs.x <= v2fe.x) {
			for (int i = (int)v2fs.x; i <= (int)v2fe.x; i++) {
				image.setPixel(i, (int)(y + 0.5), ls.getStart().color);
				y += m;
			}
		}
		else {
			for (int i = (int)v2fe.x; i <= (int)v2fs.x; i++) {
				image.setPixel(i, (int)(y + 0.5), ls.getStart().color);
				y += m;
			}
		}
	}
	else {
		if (v2fs.y <= v2fe.y) {
			for (int i = (int)v2fs.y; i <= (int)v2fe.y; i++) {
				image.setPixel(v2fs.x, i, ls.getStart().color);
			}
		}
		else {
			for (int i = (int)v2fe.y; i <= (int)v2fs.y; i++) {
				image.setPixel(v2fs.x, i, ls.getStart().color);
				y += m;
			}
		}
	}
}

/**
 * @brief Funkcja odpowiedzialna za narysowanie prymitywu na tle okna
 * 
 * @param sprite Obiekt typu Sprite reprezentujacy mozliwa do narysowania edytowalna teksture Texture
 * @param texture Obiekt typu Texture odpowiedzialny za grafike znajdujaca sie w pamieci karty graficznej i moze byc wykorzystany do rysowania
 * @param image Obiekt typu Image odpowiedzialny za ladowanie, manipulowanie oraz zapisywanie obrazow 
 * @param ls Wektor obiektow typu LineSegment, ktory ma zostac wyswietlony na tle okna. Reprezentuje prymityw w tle
 */
void drawBackgroundPrimitive(sf::Sprite& sprite, sf::Texture& texture, sf::Image& image, std::vector<LineSegment> ls) {
	for(int i=0;i<ls.size();i++)
		drawLineBackground(image, ls[i]);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
}

/**
 * @brief Funkcja odpowiedzialna za wypelnienie ksztaltu na tle okna
 * 
 * @param x Zmienna odpowiedzialna za pozycje x punktu startowego do wypelnienia 
 * @param y Zmienna odpowiedzialna za pozycje y punktu startowego do wypelnienia 
 * @param ct Obiekt typu Color odpowiedzialny za reprezentacje koloru tla
 * @param cw Obiekt typu Color odpowiedzialny za reprezentacje koloru wypelnienia
 * @param image Obiekt typu Image odpowiedzialny za ladowanie, manipulowanie oraz zapisywanie obrazow 
 */
void wypelnijR(int x, int y, sf::Color ct, sf::Color cw, sf::Image& image) {
	if (image.getPixel(x, y) == cw) return;
	else if (image.getPixel(x, y) != ct)return;
	else {
		image.setPixel(x, y, cw);
		//std::cout << x << " " << y << std::endl;
		wypelnijR(x + 1, y, ct, cw, image);
		wypelnijR(x - 1, y, ct, cw, image);
		wypelnijR(x, y + 1, ct, cw, image);
		wypelnijR(x, y - 1, ct, cw, image);
		return;
	}
}