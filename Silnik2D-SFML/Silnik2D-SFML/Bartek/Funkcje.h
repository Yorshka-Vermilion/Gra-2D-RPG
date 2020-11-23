#pragma once

//Czyszczenie bitmap

void WyczyscBitmapy(Obiekt obj[]) { //Czyszczenie tablicy z obiektami zawierajacymi bitmapy
	for (int i = 0; i < (sizeof(obj) / sizeof(*obj)); i++) {
		obj[i].WyczyscBitmape();
	}
}


