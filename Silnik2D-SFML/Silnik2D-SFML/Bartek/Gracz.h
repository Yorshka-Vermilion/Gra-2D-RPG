#pragma once
#include "Obiekt.h"
#include "../Sebix/Statystyki.h"

/**
 * @brief Klasa opisujaca gracza
 * 
 */
class Gracz :
	public Obiekt
{
private:
	/// Prostokatny ksztalt gracza (jego wymiary, ramka)
	sf::RectangleShape ksztalt; 
	
	/// Typ logiczny odpowiadajacy za wlaczenie i wylaczenie opcji debugu (niezaimplementowane)
	bool debug = false;
	
public:
	double zycie = 0;
	double mana = 0;
	double exp = 0;
	std::string nazwa;

	double maxZycie;
	double maxMana;
	double maxExp;
	int level = 1;
	bool levelUp = false;
	Statystyki* statystyki;
	/**
	 * @brief Konsturktor obiektu Gracz
	 * 
	 * @param sciezka Sciezka do pliku z obrazem gracza
	 * @param pozycja Pozycja poczatkowa gracza
	 * @param ksztalt Obiekt RectangleShape zawierajacy ksztalt gracza
	 */
	Gracz(std::string sciezka, sf::Vector2f pozycja, double maxZycie, double maxMana, double maxExp) : Obiekt(sciezka, pozycja) {
		this->statystyki = new Statystyki(3, 0.1, 0.1, 0.1);
		this->maxZycie = maxZycie + this->statystyki->obliczSila(maxZycie);
		this->maxMana = maxMana + this->statystyki->obliczInteligencja(maxMana);
		//std::cout << this->maxZycie << " Creator " << this->maxMana << std::endl;
		this->maxExp = maxExp;
		this->zycie = maxZycie;
		this->mana = maxMana;
		this->ksztalt = sf::RectangleShape(sf::Vector2f(this->sprajt.getTexture()->getSize()));
		this->setOriginOnMiddle();
		this->sprajt.setPosition(pozycja);
		this->ksztalt.setOrigin(this->sprajt.getOrigin());
		this->ksztalt.setPosition(pozycja);
	}


	~Gracz() {
		delete(this->statystyki);
	}

	/**
	 * @brief Funkcja wlaczajaca tryb debugowania
	 * 
	 */
	void debuguj() {
		this->debug = true;
	}

	/**
	 * @brief Przeniesienie obiektu (gracza) na pozycje podana w argumencia
	 * 
	 * @param gdzie Pozycja na ktora gracz ma zostac przeniesiony
	 */
	void rusz(sf::Vector2f gdzie) { 
		this->ksztalt.setPosition(gdzie);
		this->sprajt.setPosition(gdzie);
	}

	/**
	 * @brief Rysowanie obiektu (gracza)
	 * 
	 * @param cel Obiekt typu RenderTarget wskazujacy na cel w ktorym bedzie renderowany sprite
	 */
	void draw(sf::RenderTarget* cel) { 
	//	cel->draw(this->ksztalt);
		cel->draw(this->sprajt);
		
		//draw2DPoint(Point2D(sf::Vector2f(this->sprajt.getOrigin()), sf::Color::Magenta), cel);

	}
	/**
	 * @brief Zwraca aktualna pozycje obiektu (gracza)
	 * 
	 * @return sf::Vector2f Aktualna pozycja gracza
	 */
	sf::Vector2f pobierzPozycje() {
		return this->ksztalt.getPosition();
	}

	double zwrocObecnyStanZdrowia() {
		return this->zycie;
	}

	double zwrocObecnyStanMany() {
		return this->mana;
	}

	void zadajObrazenia(double ile = 1) {
		if(this->zycie>0)
			this->zycie -= ile;
	}

	void uleczObrazenia(double ile = 1) {
		if (this->zycie < this->maxZycie)
			this->zycie+=ile;
	}

	void odejmijMane(double ile = 1) {
		if (this->mana > 0)
			this->mana-=ile;
	}

	void ladujMane(double ile = 1) {
		if (this->mana < this->maxMana)
			this->mana+=ile;
	}

	void dodajExp(double ilosc){
		//std::cout << this->exp << " - " << this->maxExp << " -- " << this->level <<  std::endl;
		if (this->exp < this->maxExp){
			this->exp += ilosc;
			sprawdzLevel();
		}
	}

	void sprawdzLevel() {
		if (this->exp >= this->maxExp) {
			int exptmp = this->exp - this->maxExp;
			this->level++;
			this->exp = exptmp;
			this->maxExp += this->maxExp * 0.2;
			this->zmienStanLevel();
			this->setFullZycie();
			this->setFullMana();
			//std::cout << "Zmiana" << std::endl;
		}
	}

	int zwrocLevel() {
		return this->level;
	}

	void zmienStanLevel() {
		if (this->levelUp == false) this->levelUp = true;
		else this->levelUp = false;
	}

	double zwrocObecnyStanExp() {
		return this->exp;
	}

	void setNazwa(std::string nazwa) {
		this->nazwa = nazwa;
	}

	std::string zwrocNazwa() {
		return this->nazwa;
	}

	void setFullZycie() {
		this->zycie = maxZycie;
	}

	void setFullMana() {
		this->mana = maxMana;
	}

	bool isDead() {
		if (this->zycie < 0) return true;
	}
};

