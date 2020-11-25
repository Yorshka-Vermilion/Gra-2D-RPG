#pragma once
#include "Animacja.h"
#include "../Sebix.h"
#include "../Przemek/rysowanie.h"
#include "Gracz.h"
#include "ObslugaRuchuGracza.h"
#include "Demo.h"
#include "BitmapHandler.h"
#include "Funkcje.h"

class Demo : public Stan
{
	sf::RenderWindow* window; // Okno
	sf::Event* event; // Wskaznik na eventy
	Obiekt* testObrazu;
	Animacja* testAnimacji;
	Gracz* gracz; // Wskaznik na obiekt gracza
	ObslugaRuchuGracza* gRuch; // Wskaznik na obsluge ruchu gracza
	BitmapHandler* bitmapa; //Obsluga bitmapy
	BitmapHandler* obj[3];
	sf::Texture tekstura;
	sf::Sprite sprajt;
	float dtime;
	bool nacisnieto;
	//----------------------------------------------
	sf::Vector2f v1;
	std::vector<sf::Vector2f> v2,v3,v4,v10;
	std::vector<sf::Vector2f> vls1, vls2, vls3, vls4;
	std::vector<sf::Vector2f> vo1, vo2, vo3, vo4, vo5;
	Point2D p2d;
	LineSegment ls1,ls2,ls3,ls4,ls5;
	Point2DArray p2da2,p2da3,p2da4,p2da10;
	Moveport mp;
	std::vector<LineSegment> lss;
	CirclePrimitive cp;


	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	//---------------------------------------------
	std::vector<Point2D> p2dv;
	Viewport vp;
	BoundingBox bb;
	


	int opcja = 0;
public:
	Demo(sf::RenderWindow* window, std::stack<Stan*>* stos, sf::Event* event) : Stan(window, stos, event) {
		this->obj[0] = new BitmapHandler();
		this->obj[1] = new BitmapHandler();
		this->obj[2] = new BitmapHandler();
		this->window = window;
		this->event = event;
		this->dtime = 0.1;
	}

	~Demo() {
		delete(this->window);
		delete(this->gracz);
		delete(this->gRuch);
		delete(this->event);
		delete(this->testAnimacji);
		delete(this->testObrazu);
	}

	void demoWczytaj() { /// Wczytuje testowane obiekty
		//Demo obrazka
		this->testObrazu = new Obiekt("Obraz.jpg", sf::Vector2f(50, 50));
		//Demo animacji
		this->testAnimacji = new Animacja("testanimacja.png", 10, 10, 765, 540, 32, 0.1);
		//Demo gracza
		this->gracz = new Gracz("Postac.png", sf::Vector2f(100, 100), sf::RectangleShape(sf::Vector2f(79, 63)));
		this->gRuch = new ObslugaRuchuGracza(gracz, 300);
		//Demo bitmap
		this->bitmapa = new BitmapHandler();
		this->bitmapa->stworz(40, 40);
		this->tekstura.loadFromImage(this->bitmapa->obraz);
		this->sprajt.setTexture(this->tekstura);
		this->bitmapa->zapisz("bitmapa.bmp");

		//this->testAnimacji->WyczyscBitmape(); // Dziala

		//---------------------------------------------------
		//pkt
		this->p2d = Point2D(sf::Vector2f(100.f,100.f), sf::Color::White);
		
		//linia
		v2.push_back(sf::Vector2f(100.f, 100.f));
		v2.push_back(sf::Vector2f(400.f, 400.f));
		this->p2da2 = Point2DArray(v2, sf::Color(255, 255, 255));

		//trojkat/linia-zamk/linia-otw
		v3.push_back(sf::Vector2f(50.f, 50.f));
		v3.push_back(sf::Vector2f(50, 300.f));
		v3.push_back(sf::Vector2f(300.f, 50.f));
		this->p2da3 = Point2DArray(v3,sf::Color::White);
		

		//prostokat
		v4.push_back(sf::Vector2f(100.f, 100.f));
		v4.push_back(sf::Vector2f(100.f, 400.f));
		v4.push_back(sf::Vector2f(400.f, 400.f));
		v4.push_back(sf::Vector2f(400.f, 100.f));
		this->p2da4 = Point2DArray(v4, sf::Color::White);
		
		//zbior pkt
		v10.push_back(sf::Vector2f(50.f, 90.f));
		v10.push_back(sf::Vector2f(612.f, 412.f));
		v10.push_back(sf::Vector2f(203.f, 317.f));
		v10.push_back(sf::Vector2f(231.f, 278.f));
		v10.push_back(sf::Vector2f(731.f, 521.f));
		v10.push_back(sf::Vector2f(121.f, 512.f));
		v10.push_back(sf::Vector2f(521.f, 512.f));
		v10.push_back(sf::Vector2f(381.f, 278.f));
		v10.push_back(sf::Vector2f(217.f, 482.f));
		v10.push_back(sf::Vector2f(400.f, 400.f));
		this->p2da10 = Point2DArray(v10, sf::Color::White);	

		//tlo
		image.create(800, 800, sf::Color::Green);
		texture.loadFromImage(image);
		sprite.setTexture(texture);

		//okrag
		cp = CirclePrimitive(Point2D(sf::Vector2f(400, 400), sf::Color::Red), 200);

		//prymityw w tle
		vls1.push_back(sf::Vector2f(0.f, 0.f));
		vls1.push_back(sf::Vector2f(0.f, 50.f));
		vls2.push_back(sf::Vector2f(0.f, 50.f));
		vls2.push_back(sf::Vector2f(50.f, 50.f));
		vls3.push_back(sf::Vector2f(50.f, 50.f));
		vls3.push_back(sf::Vector2f(50.f, 0.f));
		vls4.push_back(sf::Vector2f(50.f, 0.f));
		vls4.push_back(sf::Vector2f(0.f, 0.f));

		ls1 = LineSegment(vls1, sf::Color::Red);
		ls2 = LineSegment(vls2, sf::Color::Red);
		ls3 = LineSegment(vls3, sf::Color::Red);
		ls4 = LineSegment(vls4, sf::Color::Red);

		lss.push_back(ls1);
		lss.push_back(ls2);
		lss.push_back(ls3);
		lss.push_back(ls4);

		//nalozenie prymitywu w tle
		drawBackgroundPrimitive(this->sprite, this->texture, this->image, lss);
		
		//prymityw odcinajacy
		vo1.push_back(sf::Vector2f(50.f, 90.f));
		vo1.push_back(sf::Vector2f(612.f, 412.f));
		vo2.push_back(sf::Vector2f(203.f, 317.f));
		vo2.push_back(sf::Vector2f(231.f, 278.f));
		vo3.push_back(sf::Vector2f(731.f, 521.f));
		vo3.push_back(sf::Vector2f(121.f, 512.f));
		vo4.push_back(sf::Vector2f(521.f, 512.f));
		vo4.push_back(sf::Vector2f(381.f, 278.f));
		vo5.push_back(sf::Vector2f(217.f, 482.f));
		vo5.push_back(sf::Vector2f(400.f, 400.f));

		ls1 = LineSegment(vo1, sf::Color::Red);
		ls2 = LineSegment(vo2, sf::Color::Red);
		ls3 = LineSegment(vo3, sf::Color::Red);
		ls4 = LineSegment(vo4, sf::Color::Red);
		ls5 = LineSegment(vo5, sf::Color::Red);

		lss.clear();
		lss.push_back(ls1);
		lss.push_back(ls2);
		lss.push_back(ls3);
		lss.push_back(ls4);
		lss.push_back(ls5);


		mp = Moveport(p2da4);

		//-------------------------------------------
		p2dv.push_back(Point2D(sf::Vector2f(100, 100), sf::Color::Blue));
		p2dv.push_back(Point2D(sf::Vector2f(350, 350), sf::Color::Blue));
		this->vp = Viewport(p2dv);

		p2dv.push_back(Point2D(sf::Vector2f(400, 400), sf::Color::Blue));
		p2dv.push_back(Point2D(sf::Vector2f(500, 500), sf::Color::Blue));
		this->bb = BoundingBox(p2dv);

	}

	void draw(sf::RenderTarget* target) {/// Funkcja rysujaca
		if (opcja == 0)target->draw(this->testObrazu->sprajt); // Pokazanie obrazu
		else if (opcja == 1) {
			this->gracz->draw(target);
			this->gracz->rotuj(20); // Przekrecenie gracza
			this->gracz->przeskaluj(sf::Vector2f(2, 2)); // Przeskalowanie gracza
		}// Pokazanie gracza i ruchu
		else if (opcja == 2)testAnimacji->animuj(target, this->dtime); // Pokazanie animacji
		else if (opcja == 3)target->draw(this->sprajt); // Pokazanie bitmapy
		else if (opcja == 4) { // Pokazanie czyszczenia bitmap
			WyczyscBitmapy(this->obj);
			opcja++;
			std::cout << "Wyczyszczono bitmapy" << std::endl;
		}
		else if (opcja == 5) { // Pokazanie myszki
			std::cout << this->pozycja_kursora_w_oknie.x << " : " << this->pozycja_kursora_w_oknie.y << std::endl;
		}
		else if (opcja == 6) {// Pokazanie pkt
			draw2DPoint(p2d, target);
		}
		else if (opcja == 7) {// Pokazanie zbioru pkt
			draw2DPoints(Point2DArray(v10, sf::Color::White), target);
		}
		else if (opcja == 8) {// Pokazanie linii otwartej
			drawLineOtwarta(p2da10, target);
		}

		else if (opcja == 9) {// Pokazanie linii zamknietej
			drawLineZamknieta(p2da10, target);
		}
		else if (opcja == 10) {// Pokazanie linii przez biblioteke
			for (int i = 0; i < 800; i += 50) {
				draw2DLine(Point2D(sf::Vector2f(400, 400), sf::Color::White), Point2D(sf::Vector2f(i, 0), sf::Color::White), target);
			}
			for (int i = 0; i < 800; i += 50) {
				draw2DLine(Point2D(sf::Vector2f(400, 400), sf::Color::White), Point2D(sf::Vector2f(i, 800), sf::Color::White), target);
			}
			for (int i = 0; i < 800; i += 50) {
				draw2DLine(Point2D(sf::Vector2f(400, 400), sf::Color::White), Point2D(sf::Vector2f(0, i), sf::Color::White), target);
			}
			for (int i = 0; i < 800; i += 50) {
				draw2DLine(Point2D(sf::Vector2f(400, 400), sf::Color::White), Point2D(sf::Vector2f(800, i), sf::Color::White), target);
			}
		}
		else if (opcja == 11) {// Pokazanie linii przez algorytm przyrostowy
			for (int i = 0; i < 800; i += 50) {
				wykonaj(Point2D(sf::Vector2f(400, 400), sf::Color::White), Point2D(sf::Vector2f(i, 0), sf::Color::White), target);
			}
			for (int i = 0; i < 800; i += 50) {
				wykonaj(Point2D(sf::Vector2f(400, 400), sf::Color::White), Point2D(sf::Vector2f(i, 800), sf::Color::White), target);
			}
			for (int i = 0; i < 800; i += 50) {
				wykonaj(Point2D(sf::Vector2f(400, 400), sf::Color::White), Point2D(sf::Vector2f(0, i), sf::Color::White), target);
			}
			for (int i = 0; i < 800; i += 50) {
				wykonaj(Point2D(sf::Vector2f(400, 400), sf::Color::White), Point2D(sf::Vector2f(800, i), sf::Color::White), target);
			}
		}
		else if (opcja == 12) {// Rysowanie pustego trojkata
			draw2DEmpty(p2da3, target);
		}
		else if (opcja == 13) {// Rysowanie pelnego trojkata
			draw2DTriangle(p2da3, target);
		}
		else if (opcja == 14) {// Rysowanie pustego prostokata
			draw2DEmpty(p2da4, target);
		}
		else if (opcja == 15) {// Rysowanie pelnego prostokata
			draw2DQuad(p2da4, target);
		}
		else if (opcja == 16) {// Rysowanie okregu czterokrotna symetria
			cp.drawFourCircle(target);
		}
		else if (opcja == 17) {// Rysowanie okregu osmiokrotna symetria
			cp.drawEightCircle(target);
		}
		else if (opcja == 18) {// Rysowanie prymitywu do wypelnienia
			target->draw(sprite);
		}
		else if (opcja == 19) {// Wypelnienie prymitywu farba przy pomocy algorytmu
			wypelnijR(25, 25, sf::Color::Green, sf::Color::Red, image);
			texture.loadFromImage(image);
			sprite.setTexture(texture);
			target->draw(sprite);
		}
		else if (opcja == 20) {// Zmiana wspolrzednych
			
			vp.wyswietl_wspolrzedne();
			vp.zmien_wspolrzedne(Point2D(sf::Vector2f(700, 700), sf::Color::Blue));
			std::cout << "--------------------------------------" << std::endl;
			vp.wyswietl_wspolrzedne();
		}
		else if (opcja == 21) {// Brak kolizji miedzy prymitywami
			bb.prostokat_obcinajacy(target);
			bb.prostokat_obcinajacy_2(target);
			bb.kolizja();
		}
		else if (opcja == 22) {// Kolizja miedzy prymitywami
			bb.zmien_wspolrzedne(Point2D(sf::Vector2f(800, 800), sf::Color::Red));
			bb.prostokat_obcinajacy(target);
			bb.prostokat_obcinajacy_2(target);
			bb.kolizja();
		}
		else if (opcja == 23) {
			mp.drawViewport(target);
			mp.moveViewport();
			mp.cutViewportLines(lss,target);
		}
		else exit(0);
	}

	void update(const float& dtime) { /// Funkcja aktualizujaca stan
		gRuch->update(dtime);
		this->dtime = dtime;
		sprawdzMysz();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
			if (!this->nacisnieto) {
				this->nacisnieto = true;
				this->opcja++;
			}
		}
		else {
			this->nacisnieto = false;
		}
	}

};

