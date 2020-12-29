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
};

