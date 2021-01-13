#pragma once
#include <vector>
#include "Dzwiek.h"

/**
 * @brief Klasa obslugujaca dzwieki
 *
 */
class Dzwieki
{


public:

	///Vector przechowujacy dzwieki
	std::vector<Dzwiek*> lista_dzwiekow;


	/**
	* @brief Konstruktor dzwiekow
	*/
	Dzwieki() {
		this->lista_dzwiekow.push_back(new Dzwiek("castowanie.wav"));
	}

	/**
	* @brief Funkcja aktualizujaca stan wszystkich dzwiekow w vectorze lista_dzwiekow
	*/
	void update() {
		for (size_t i = 0; i < this->lista_dzwiekow.size(); i++) {
			this->lista_dzwiekow.at(i)->update();
		}
	}


	/**
	* @brief Funkcja wlaczajaca dany dzwiek z lista_dzwiekow
	*
	* @param i Index pozadanego dzwieku
	*/
	void graj(int i) {
		if (this->lista_dzwiekow.size() > i) {
			this->lista_dzwiekow.at(i)->graj();
		}
	}

	/**
	* @brief Funkcja wylaczajaca dany dzwiek z lista_dzwiekow
	*
	* @param i Index pozadanego dzwieku
	*/
	void stop(int i) {
		if (this->lista_dzwiekow.size() > i) {
			this->lista_dzwiekow.at(i)->stop();
		}
	}
};

