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
	/// Zycie gracza
	double zycie = 0;
	/// Mana gracza
	double mana = 0;
	/// Doswiadczenie gracza
	double exp = 0;
	/// Nazwa gracza
	std::string nazwa;
	/// Maksymalne zycie gracza
	double maxZycie;
	/// Maksymalna mana gracza
	double maxMana;
	/// Doswiadcznenie potrzebne do awansu
	double maxExp;
	/// Poziom gracza
	int level = 1;
	/// Flaga oznaczajaca czy gracz wszedl na nowy poziom doswiadczenia
	bool levelUp = false;
	/// Wskaznik na statystyki 
	Statystyki* statystyki;
	/**
	 * @brief Konsturktor obiektu Gracz
	 *
	 * @param sciezka Sciezka do pliku z obrazem gracza
	 * @param pozycja Pozycja poczatkowa gracza
	 * @param maxZycie Maksymalne zycie gracza
	 * @param maxMana Maksymalna mana gracza
	 * @param maxExp Doswiadcznenie potrzebne do awansu
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

	/**
	 * @brief Dekonstruktor gracza
	 *
	 */
	~Gracz() {
		delete(this->statystyki);
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
	/**
	 * @brief Funkcja zwraca obecny stan zdrowia gracza
	 *
	 * @return double zwraca obecna ilosc zdrowia
	 */
	double zwrocObecnyStanZdrowia() {
		return this->zycie;
	}

	/**
	 * @brief Funkcja zwraca obecny stan many gracza
	 *
	 * @return double zwraca obecna ilosc many
	 */
	double zwrocObecnyStanMany() {
		return this->mana;
	}

	/**
	 * @brief Funkcja zadaje obrazanie graczowi
	 *
	 * @param ile Ile obrazen nalezy odjac od puli zdrowia gracza
	 */
	void zadajObrazenia(double ile = 1) {
		if (this->zycie > 0)
			this->zycie -= ile;
	}

	/**
	 * @brief Funkcja leczy gracza
	 *
	 * @param ile Ile punktow zycia nalezy dodac do puli zdrowia gracza
	 */
	void uleczObrazenia(double ile = 1) {
		if (ile + this->zycie >= maxZycie) this->zycie = this->maxZycie;
		if (this->zycie < this->maxZycie)
			this->zycie += ile;
	}

	/**
	 * @brief Funkcja zabiera mane gracza
	 *
	 * @param ile Ile many nalezy odjac z puli many
	 */
	void odejmijMane(double ile = 1) {
		if (this->mana - ile <= 0) this->mana = 0;
		if (this->mana > 0)
			this->mana -= ile;
	}

	/**
	 * @brief Funkcja dodaje mane graczowi
	 *
	 * @param ile Ile many nalezy dodac do puli many
	 */
	void ladujMane(double ile = 1) {
		if (ile + this->mana >= maxMana) this->mana = this->maxMana;
		if (this->mana < this->maxMana)
			this->mana += ile;
	}

	/**
	 * @brief Funkcja dodaje doswiadczenie graczowi
	 *
	 * @param ilosc Ile doswiadczenia nalezy dodac
	 */
	void dodajExp(double ilosc) {
		//std::cout << this->exp << " - " << this->maxExp << " -- " << this->level <<  std::endl;
		if (this->exp < this->maxExp) {
			this->exp += ilosc;
			sprawdzLevel();
		}
	}

	/**
	 * @brief Funkcja sprawdza czy gracz wszedl na nowy poziom doswiadczenia
	 *
	 */
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

	/**
	 * @brief Funkcja zwraca poziom gracza
	 * @return int zwraca wysokosc poziomu gracza
	 */
	int zwrocLevel() {
		return this->level;
	}

	/**
	 * @brief Funkcja zmienia flage levelUp na przeciwny stan
	 *
	 */
	void zmienStanLevel() {
		if (this->levelUp == false) this->levelUp = true;
		else this->levelUp = false;
	}

	/**
	 * @brief Funkcja zwraca opecna ilosc doswiadczenia gracza
	 * @return double zwraca obecna ilosc punktow doswiadczenia
	 */
	double zwrocObecnyStanExp() {
		return this->exp;
	}

	/**
	 * @brief Funkcja ustawia nazwe gracza
	 *
	 */
	void setNazwa(std::string nazwa) {
		this->nazwa = nazwa;
	}

	/**
	 * @brief Funkcja zwraca nazwe gracza
	 * @return string zwraca obecna nazwe gracza
	 */
	std::string zwrocNazwa() {
		return this->nazwa;
	}

	/**
	 * @brief Funkcja ustawia zycie gracza na maxZycie
	 *
	 */
	void setFullZycie() {
		this->zycie = maxZycie;
	}

	/**
	 * @brief Funkcja ustawia mane gracza na maxMana
	 *
	 */
	void setFullMana() {
		this->mana = maxMana;
	}

	/**
	 * @brief Funkcja sprawdza czy gracz nie zyje, jesli umarl (jeko zycie spadlo do zera) zwraca true
	 * @return true zwraca prawde jezeli zdrowie gracza spadlo na poziom smiertelny
	 */
	bool isDead() {
		if (this->zycie <= 0) return true;
	}
};

