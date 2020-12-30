#pragma once
#include <vector>
#include "Dzwiek.h"

class Dzwieki
{


public:
	std::vector<Dzwiek*> lista_dzwiekow;

	Dzwieki() {
		this->lista_dzwiekow.push_back(new Dzwiek("castowanie.wav"));
	}

	void update() {
		for (size_t i = 0; i < this->lista_dzwiekow.size(); i++) {
			this->lista_dzwiekow.at(i)->update();
		}
	}

	void graj(int i) {
		if (this->lista_dzwiekow.size() > i) {
			this->lista_dzwiekow.at(i)->graj();
		}
	}

	void stop(int i) {
		if (this->lista_dzwiekow.size() > i) {
			this->lista_dzwiekow.at(i)->stop();
		}
	}
};

