#pragma once
#include "../Bartek/Obiekt.h";
/**
 * @brief Klasa odpowiada za reprezentacje graficzna dialogow oraz interakcji
 *
 */
class OknoDialog : public Obiekt {
	/// <summary>
	/// wynik interakcji z obiektem/postacia
	/// </summary>
	int wynik = 0;
	/// <summary>
	/// czcionka reprezentujaca tresc dialogow w sposob graficzny
	/// </summary>
	sf::Font czcionka;
	/// <summary>
	/// tresc glownej wiadomosci graficznej z dialogu
	/// </summary>
	sf::Text trescOkno;
	/// <summary>
	/// tresc pierwszej odpowiedzi wiadomosci graficznej z dialogu
	/// </summary>
	sf::Text odp1;
	/// <summary>
	/// tresc drugiej odpowiedzi wiadomosci graficznej z dialogu
	/// </summary>
	sf::Text odp2;
	/// <summary>
	/// tresc pierwszego wyniku wiadomosci graficznej z dialogu
	/// </summary>
	sf::Text result1;
	/// <summary>
	/// tresc drugiego wyniku wiadomosci graficznej z dialogu
	/// </summary>
	sf::Text result2;
public:
		/**
		 * @brief Konstruktor odpowiedzialny za okna dialgou w rozgrywce
		 *
		 * @param sciezka odpowiada za znajdowanie sie pliku reprezentujacego tlo okna
		 * @param pozycja odpowaida za pozycje w ktorej ma sie znajdowac okno
		 */
	OknoDialog(std::string sciezka, sf::Vector2f pozycja) : Obiekt(sciezka, pozycja) {
		this->setOriginOnMiddle();
		this->trescOkno = this->zrobTekst("Bandwidth 8x8.ttf", sf::Vector2f(0,0));
		this->odp1 = this->zrobTekst("Bandwidth 8x8.ttf", sf::Vector2f(0, 0));
		this->odp2 = this->zrobTekst("Bandwidth 8x8.ttf", sf::Vector2f(0, 0));
		this->result1 = this->zrobTekst("Bandwidth 8x8.ttf", sf::Vector2f(0, 0));
		this->result2 = this->zrobTekst("Bandwidth 8x8.ttf", sf::Vector2f(0, 0));
		this->przestaw(sf::Vector2f(pozycja.x/2, pozycja.y/4));
		this->trescOkno.setPosition(sf::Vector2f(pozycja.x / 2 - 150,30 + pozycja.y / 7));
		this->odp1.setPosition(sf::Vector2f(pozycja.x / 2 - 150, 90 + pozycja.y / 7));
		this->odp2.setPosition(sf::Vector2f(pozycja.x / 2 - 150, 150 + pozycja.y / 7));
		this->result1.setPosition(sf::Vector2f((pozycja.x/2) - 250,  pozycja.y / 4));
		this->result2.setPosition(sf::Vector2f((pozycja.x/2) - 100,  pozycja.y / 4));
		this->przeskaluj(sf::Vector2f(3,3));
	}

/**
* @brief Funkcja tworzaca reprezentacje graficzna w formie tekstu
*
* @param sciezka odpowiada za znajdowanie pliku reprezentujacego czcionke
* @param pozycja odpowaida za pozycje w ktorej ma sie znajdowac tekst
* @return Text zwraca gotowy obraz reprezentujacy wiadomosc
*/
	sf::Text zrobTekst(std::string sciezka, sf::Vector2f pozycja) {
		sf::Text text;
		if (!this->czcionka.loadFromFile(sciezka)) {
			std::cout << "Nie udalo sie zaladowac czcionki" << std::endl;
		}
		text.setFont(czcionka);
		text.setFillColor(sf::Color::White);
		text.setOutlineColor(sf::Color::Black);
		text.setCharacterSize(16);
		text.setOutlineThickness(2);
		sf::FloatRect center = text.getLocalBounds();
		text.setOrigin(center.left + center.width / 2, center.top + center.height / 2);
		text.setPosition(pozycja);
		return text;
	}
	/**
 * @brief Funkcja odpowiadajca za rysowanie okna
 * @param cel odpowiada za okno w którym ma zostac narysowany obiekt
 */
	void draw(sf::RenderTarget* cel) {
		cel->draw(this->sprajt);
		if (this->wynik == 0) {
		cel->draw(this->trescOkno);
		cel->draw(this->odp1);
		cel->draw(this->odp2);
		}
		else if(this->wynik == 1)
			cel->draw(this->result1);
		else if(this->wynik == 2)
			cel->draw(this->result2);
	}

	/**
 * @brief Funkcja odpowiadajca za ustawienie odpowiednich wiadomosci dialogu
 * @param tresc tresc wiadomosci glownej w dialogu
 * @param odp1 tresc pierwszej odpowiedzi w dialogu
 * @param odp2 tresc drugiej odpowiedziw dialogu
 * @param result1 tresc pierwszego wyniku z dialogu
 * @param result2 tresc drugiego wyniku z dialogu
 */
	void ustawInterakcje(std::string tresc, std::string odp1, std::string odp2, std::string result1, std::string result2) {
		this->trescOkno.setString(tresc);
		this->odp1.setString("1. " + odp1);
		this->odp2.setString("2. " + odp2);
		this->result1.setString(result1);
		this->result2.setString(result2);
	}
	/**
* @brief Funkcja odpowiadajca za ustawienie odpowiedniej wartosci definiujacej rezultat dialogu
* @param x wartosc ustalajaca wynik uzyskanej interakcji
*/
	void rozegrajInterakcje(int x) {
		if (x == 1)
			this->wynik = 1;
		else if (x == 2) this->wynik = 2;
	}
};