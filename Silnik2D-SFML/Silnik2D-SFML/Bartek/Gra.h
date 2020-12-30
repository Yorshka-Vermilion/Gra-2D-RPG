#pragma once
#include "Stan.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Mapa.h"
#include <iostream>
#include "../Sebix/Camera.h"
#include "RzucanieZaklec.h"
#include "Dzwieki.h"

/**
 * @brief Klasa w ktorej bedzie znajdowal sie kod gry
 * 
 */
class Gra : public Stan
{
	Mapa* map;
	Obiekt* maska;
	Gracz* gracz;
	ObslugaRuchuGracza* gRuch;
	HUD* hud;
	DrzewoDialogow* drzewo;
	Camera* cameraPlayer;
	std::vector<Animacja*> animacje;
	RzucanieZaklec* rzucanie_zaklec;
	Dzwieki* dzwieki;

	bool LCTRL;

public:
	Gra(sf::RenderWindow* window, std::stack<Stan*>* stos, sf::Event* event,Gracz* gracz) : Stan(window, stos, event) {
		this->drzewo = new DrzewoDialogow();
		this->gracz = gracz;
		this->gRuch = new ObslugaRuchuGracza(this->gracz, 300,this->drzewo);
		this->map = new Mapa(25, window->getSize(),this->gracz);
		this->cameraPlayer = new Camera(sf::Vector2f(window->getSize().x, window->getSize().y),0.75);
		this->hud = new HUD(sf::Vector2f(window->getSize()), this->gracz);

		//Maska
		this->maska = new Obiekt("maska.png", sf::Vector2f(0, 0));
		this->maska->setOriginOnMiddle();
		this->maska->przestaw(sf::Vector2f(990, 540));
		this->maska->przeskaluj(sf::Vector2f(1.55, 1.15));
		
		//Testy
		//this->animacje.push_back(new Animacja("animacja.png", 350, 350, 32, 32, 12, 1, true, false));
		//this->animacje.push_back(new Animacja("animacja.png", 30, 350, 32, 32, 12, 0.1, true, false));
		//this->animacje.push_back(new Animacja("animacja.png", 80, 350, 32, 32, 12, 0.75, true, false));
		this->rzucanie_zaklec = new RzucanieZaklec();
		this->dzwieki = new Dzwieki();
	}

	~Gra() {
		delete(this->map);
		delete(this->maska);
		delete(this->drzewo);
		delete(this->gRuch);
		delete(this->gracz);
		delete(this->hud);
		delete(this->dzwieki);
		delete(this->rzucanie_zaklec);
		delete(this->event);
		delete(this->stos);
		delete(this->window);
	}

	void obslugaAnimacji(sf::RenderTarget* target) {
		size_t zasieg = this->animacje.size();
		for (size_t i = 0; i < zasieg; i++) {
			this->animacje.at(i)->animuj(target, this->dtime);
			if (this->animacje.at(i)->koniec()) {
				this->animacje.erase(this->animacje.begin() + i);
				i--;
				zasieg--;
			}
		}
	}

	void draw(sf::RenderTarget* target) { /// Rysowanie obiektow na ekranie
		if (!target) target = this->window;
		target->setView(this->cameraPlayer->returnView());
		this->map->draw(target);
		this->gracz->draw(target);
		this->rzucanie_zaklec->draw(target, pozycja_kursora_w_grze);
		target->setView(target->getDefaultView());
		this->maska->draw(target);
		this->hud->draw(target);

		//Testy
		//this->animacje.at(0)->animuj(target,this->dtime);
		//obslugaAnimacji(target);
	};

	void update(const float& dtime) { /// Odswiezenie stanu aktualnego "stanu"
		this->dtime = dtime;
		//std::cout << pozycja_kursora_w_grze.x << " " << pozycja_kursora_w_grze.y << std::endl;
		this->pozycja_kursora_w_grze = sf::Vector2f(this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).x, this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).y);
		this->hud->update();
		this->gRuch->update(dtime);
		this->cameraPlayer->update(this->gracz);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			this->map->Przesun(2);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
			this->map->Przesun(3);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
			this->map->Przesun(0);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C)) {
			this->map->Przesun(1);
		}
		sprawdzMysz();
		this->map->podswietlKafelki(this->pozycja_kursora_w_grze);

		while (this->window->pollEvent(*this->event)) {
			if (this->event->type == sf::Event::KeyPressed) { // Wejscie w rzucanie czarow
				if (this->event->key.code == sf::Keyboard::LControl) {
					this->LCTRL = true;
					this->dzwieki->graj(0);
				}
			}
			else if (this->event->type == sf::Event::KeyReleased) { // Wyjscie z rzucania czarow
				if (this->event->key.code == sf::Keyboard::LControl) {
					this->LCTRL = false;

					std::cout << this->rzucanie_zaklec->rzucaj() << std::endl;//Komunikat o blednej kombinacji zaklecja/za malej ilosci many itd.
					//Tylko zrobione po ludzku nie w konsoli

					this->rzucanie_zaklec->wyczyscLinie();
					this->dzwieki->stop(0);
				}
			}

			if (this->LCTRL == true) {
				if (this->event->type == sf::Event::MouseButtonPressed) {
					if (this->event->mouseButton.button == sf::Mouse::Left)
					{
						this->rzucanie_zaklec->zapiszPoczatek(pozycja_kursora_w_grze);
					}
				}
				else if (this->event->type == sf::Event::MouseButtonReleased) {
					if (this->event->mouseButton.button == sf::Mouse::Left) {
						this->rzucanie_zaklec->zapiszKoniec(pozycja_kursora_w_grze);
					}
				}
			}
			else if (this->event->type == sf::Event::Closed) {
				this->window->close(); // Potencjalny wyciek pamieci @@@@@@@@@@@@@@@@@@@@@@@@@
			}
			else {
				if (this->event->type == sf::Event::MouseButtonPressed) {
					if (this->event->mouseButton.button == sf::Mouse::Right)
					{
						this->map->zaznaczKafelek();
					}
					else if (this->event->mouseButton.button == sf::Mouse::Left)
					{
						this->map->Rusz();
					}
				}
			}
		}
		this->dzwieki->update();

		//Rozjasnienie podczas rzucania czarow
		if (this->LCTRL == true) {
			this->maska->rozjasnij(0.1, 200);
		}
		else { // Przyciemnienie z powrotem
			this->maska->przyciemnij(1);
		}
	};
};


