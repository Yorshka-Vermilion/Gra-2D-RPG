#pragma once
#include "Animacja.h"
#include "../Sebix.h"
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
	}

	void draw(sf::RenderTarget* target) {/// Funkcja rysujaca
		if (opcja == 0)target->draw(this->testObrazu->sprajt); // Pokazanie obrazu
		else if (opcja == 1) { 
			this->gracz->draw(target); 
			this->gracz->rotuj(20); // Przekrecenie gracza
			this->gracz->przeskaluj(sf::Vector2f(2,2)); // Przeskalowanie gracza
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

