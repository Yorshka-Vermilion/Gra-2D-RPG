#pragma once


/**
 * @brief Czysci obiekty BitmapHandler
 * 
 * @param obj Tablica z obiektami BitmapHandler
 */
void WyczyscBitmapy(BitmapHandler* obj[]) { 
	for (int i = 0; i < (sizeof(obj) / sizeof(obj)); i++) {
		delete(obj[i]);
	}
}


