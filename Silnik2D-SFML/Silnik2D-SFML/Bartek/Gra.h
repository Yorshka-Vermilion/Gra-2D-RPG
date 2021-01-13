#pragma once
#include "Stan.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Mapa.h"
#include <iostream>
#include "../Sebix/Camera.h"
#include "RzucanieZaklec.h"
#include "Dzwieki.h"
#include "ObslugaRuchuGracza.h"

/**
 * @brief Klasa w ktorej bedzie znajdowal sie kod gry
 * 
 */
class Gra : public Stan
{
public:
	/// Wskaznik na mape
	Mapa* map;
	/// Wskaznik na maske
	Obiekt* maska;
	/// Wskaznik na gracza
	Gracz* gracz;
	/// Wskaznik na obsluge ruchu gracza umozliwiajaca ruch
	ObslugaRuchuGracza* gRuch;
	/// Wskaznik na HUD
	HUD* hud;
	/// Wskaznik na drzewo dialogow
	DrzewoDialogow* drzewo;
	/// Wskaznik na kamere
	Camera* cameraPlayer;
	/// Vector wskaznokow na animacje
	std::vector<Animacja*> animacje;
	/// Wskaznik na klase obslugujaca rzucenia zaklec
	RzucanieZaklec* rzucanie_zaklec;
	/// Wskaznik na klase obslugujaca dzwieki
	Dzwieki* dzwieki;
	/// <summary>
	/// Wskaznik na klase obslugujaca okna dialogow
	/// </summary>
	OknoDialog* okno;

	/// <summary>
	/// Flaga sygnalizujaca stan interakcji z obiektem/postacia
	/// </summary>
	bool interakcja = false;
	/// Flaga sygnalizujaca stan przycisku lewy CTRL
	bool LCTRL;
	/// Flaga sygnalizujaca stan przycisku lewy ALT
	bool LALT = false;

	/**
	 * @brief Konstruktor gry
	 *
	 * @param window Wskaznik na okno
	 * @param stos Wskaznik na stos wskaznikow na stany
	 * @param event Wskaznik na eventy
	 * @param gracz Wskaznik na gracza
	 */
	Gra(sf::RenderWindow* window, std::stack<Stan*>* stos, sf::Event* event,Gracz* gracz) : Stan(window, stos, event) {
		this->drzewo = new DrzewoDialogow();
		this->gracz = gracz;
		this->rzucanie_zaklec = new RzucanieZaklec(this->gracz);
		//std::cout << this->gracz->maxZycie << " Gra " << this->gracz->maxMana << std::endl;
		this->gRuch = new ObslugaRuchuGracza(this->gracz, 300,this->drzewo);
		this->map = new Mapa(25, window->getSize(),this->gracz);
		this->cameraPlayer = new Camera(sf::Vector2f(window->getSize().x, window->getSize().y),0.75);
		this->hud = new HUD(sf::Vector2f(window->getSize()), this->gracz);
		this->okno = new OknoDialog("ramka.png", (sf::Vector2f)this->window->getSize());

		//Maska
		this->maska = new Obiekt("maska.png", sf::Vector2f(0, 0));
		this->maska->setOriginOnMiddle();
		this->maska->przestaw(sf::Vector2f(990, 540));
		this->maska->przeskaluj(sf::Vector2f(1.55, 1.15));
		
		//Testy
		//this->animacje.push_back(new Animacja("animacja.png", 350, 350, 32, 32, 12, 1, true, false));
		//this->animacje.push_back(new Animacja("animacja.png", 30, 350, 32, 32, 12, 0.1, true, false));
		//this->animacje.push_back(new Animacja("animacja.png", 80, 350, 32, 32, 12, 0.75, true, false));
		this->dzwieki = new Dzwieki();
	}
	/**
	 * @brief Dekonstruktor gry
	 */
	~Gra() {
		delete(this->map);
		delete(this->maska);
		delete(this->drzewo);
		delete(this->gRuch);
		delete(this->gracz);
		delete(this->hud);
		delete(this->dzwieki);
		delete(this->rzucanie_zaklec);
		delete(this->okno);
		delete(this->event);
		delete(this->stos);
		delete(this->window);
	}

	/**
	 * @brief Rysowanie obiektow na ekranie
	 *
	 * @param target Wskaznik na cel rysowania
	 */
	void draw(sf::RenderTarget* target) { /// Rysowanie obiektow na ekranie
		if (!target) target = this->window;
		target->setView(this->cameraPlayer->returnView());
		this->map->draw(target);
		this->gracz->draw(target);
		this->rzucanie_zaklec->draw(target, pozycja_kursora_w_grze);
		this->map->animuj(target, this->dtime);
		target->setView(target->getDefaultView());
		this->maska->draw(target);
		if(this->LALT == true) this->hud->zwrocStatystyki()->drawStat(target);
		if(this->interakcja == true) this->okno->draw(target);
		this->hud->draw(target);
		

		//Testy
		//this->animacje.at(0)->animuj(target,this->dtime);
		//obslugaAnimacji(target);
	};
	/**
	 * @brief Odswiezenie stanu gry
	 *
	 * @param dtime Delta czasu (timer)
	 */
	void update(const float& dtime) { /// Odswiezenie stanu aktualnego "stanu"
		this->dtime = dtime;
		//std::cout << pozycja_kursora_w_grze.x << " " << pozycja_kursora_w_grze.y << std::endl;
		this->pozycja_kursora_w_grze = sf::Vector2f(this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).x, this->window->mapPixelToCoords(this->pozycja_kursora_w_oknie, this->cameraPlayer->returnView()).y);
		sprawdzMysz();
		if (this->gracz->isDead() == true) this->stos->pop();
		if (!this->hud->sprawdzajPodswietlenia((sf::Vector2f)this->pozycja_kursora_w_oknie,this->lewy) || this->hud->returnIsAble() == false){
			this->hud->update();
			this->gRuch->update(dtime);
			this->cameraPlayer->update(this->gracz);
			this->map->update();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F5)) {
				std::remove("Save.txt");
				std::ofstream save;
				int r = this->gracz->sprajt.getColor().r;
				int g = this->gracz->sprajt.getColor().g;
				int b = this->gracz->sprajt.getColor().b;
				save.open("Save.txt", std::ios::in | std::ios::out | std::ios::trunc);
				save << this->gracz->zwrocObecnyStanZdrowia() << "\n";
				save << this->gracz->maxZycie << "\n";
				save << this->gracz->zwrocObecnyStanMany() << "\n";
				save << this->gracz->maxMana << "\n";
				save << this->gracz->zwrocLevel() << "\n";
				save << this->gracz->zwrocObecnyStanExp() << "\n";
				save << this->gracz->maxExp << "\n";
				save << this->gracz->zwrocNazwa() << "\n";
				save << this->gracz->statystyki->zwrocSila() << "\n";
				save << this->gracz->statystyki->zwrocDmg() << "\n";
				save << this->gracz->statystyki->zwrocInteligencja() << "\n";
				save << this->gracz->statystyki->zwrocIloscDostepnychPunktow() << "\n";
				save << r << "\n";
				save << g << "\n";
				save << b << "\n";
				save.close();
			}
			
			//this->map->podswietlKafelki(this->pozycja_kursora_w_grze);

			
			while (this->window->pollEvent(*this->event)) {
				if (this->event->type == sf::Event::KeyPressed) { // Wejscie w rzucanie czarow
					if (this->event->key.code == sf::Keyboard::Num1 && this->interakcja == true) {
						this->okno->rozegrajInterakcje(1);
						this->interakcja = false;
						this->map->zwrocAktualnieZaznaczona()->zwrocObiekt()->setInterakcja(false);
					}
					else if (this->event->key.code == sf::Keyboard::Num2 && this->interakcja == true) {
						this->okno->rozegrajInterakcje(2);
						this->map->zwrocAktualnieZaznaczona()->otoczenie->setRange(3);
						this->interakcja = false;
						this->map->zwrocAktualnieZaznaczona()->zwrocObiekt()->setInterakcja(false);
					}
					else if (this->event->key.code == sf::Keyboard::LControl) {
						this->LCTRL = true;
						this->dzwieki->graj(0);
					}
					else if (this->event->key.code == sf::Keyboard::LAlt) {
						this->LALT = true;
					}
					else if (this->event->key.code == sf::Keyboard::Escape) {
						this->stos->pop();
					}
				}
				else if (this->event->type == sf::Event::KeyReleased) { // Wyjscie z rzucania czarow
					if (this->event->key.code == sf::Keyboard::LControl) {
						this->LCTRL = false;

						std::cout << this->rzucanie_zaklec->rzucaj(this->map->zwrocAktualnieZaznaczona()) << std::endl;//Komunikat o blednej kombinacji zaklecja/za malej ilosci many itd.
						

						this->rzucanie_zaklec->wyczyscLinie();
						this->dzwieki->stop(0);
					}
					else if (this->event->key.code == sf::Keyboard::LAlt) {
						this->LALT = false;
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
					this->window->close();
				}
				else {
					if (this->event->type == sf::Event::MouseButtonPressed) {
						if (this->event->mouseButton.button == sf::Mouse::Right)
						{
							this->map->zaznaczKafelek();
							if (this->map->zwrocAktualnieZaznaczona()->otoczenie->zwrocInterakcja() == true) {
								this->interakcja = true;
								this->okno->ustawInterakcje("Witaj magu! Czego chcesz?", "Zupelnie niczego", "Twojej glowy","Odejdz wiec, tylko uwazaj na siebie","Walczmy zatem!");
							}
						}
						else if (this->event->mouseButton.button == sf::Mouse::Left)
						{
							if(this->map->Rusz() == true){
								this->gracz->ladujMane(this->gracz->maxMana * 0.1);
								if (this->interakcja == true) this->interakcja = false;
								for (int i = 0; i < this->map->zwrocDystansTworzenia(); i++) {
									for (int j = 0; j < this->map->zwrocDystansTworzenia(); j++) {
										if(this->map->plytki[i][j]->otoczenie != nullptr)
											this->map->plytki[i][j]->zwrocObiekt()->atak(this->gracz,i,j);
									}
								}
							}
						}
					}
				}
			}
			this->map->podswietlKafelki(this->pozycja_kursora_w_grze);
			this->dzwieki->update();

			//Rozjasnienie podczas rzucania czarow
			if (this->LCTRL == true) {
				this->maska->rozjasnij(0.1, 200);
			}
			else { // Przyciemnienie z powrotem
				this->maska->przyciemnij(1);
			}
		}
	};
};


