#include "terreno.h"
#include <iostream>

Terreno::Terreno(int material): material(material) {}

int Terreno::obtener_id_material() {
	return material;
}

int Terreno::obtener_cantidad_especia() {
	//std::cout << "paso por metodo de terreno en obtener_cantidad_especia"
	//<< std::endl;
	return 0;
}

int Terreno::reducir_especia(int cantidad_a_reducir) {
	//std::cout << "paso por metodo de terreno en reducir_especia"
	//<< std::endl;
	return 0;
}
