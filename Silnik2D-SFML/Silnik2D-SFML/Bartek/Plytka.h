#pragma once
#include "Obiekt.h"
#include "Gracz.h"

class Plytka : public Obiekt
{
	/// Zmienna sluzaca do sprawdzania czy mozna przejsc na plytke
	bool dostepna = true; 
	Gracz* gracz = nullptr;

public:
	Plytka(std::string sciezka, sf::Vector2f pozycja) : Obiekt(sciezka, pozycja) {
		

	}
	
	
	
	void PrzypiszGracza(Gracz* gracz) {
		this->gracz = gracz;
	}
	
	// Ustawia zmienna dostepna.
	void ZmienDostepnosc(bool jak) {
		this->dostepna = jak;
	}


};

