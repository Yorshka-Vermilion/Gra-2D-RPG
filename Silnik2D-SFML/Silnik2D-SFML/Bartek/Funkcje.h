#pragma once

//Czyszczenie bitmap

void WyczyscBitmapy(BitmapHandler* obj[]) { ///Czyszczenie tablicy z obiektami zawierajacymi bitmapy
	for (int i = 0; i < (sizeof(obj) / sizeof(obj)); i++) {
		delete(obj[i]);
	}
}


