#include "especia.h"
#include <iostream>
#define ESPECIAFUERTE 32
#define ESPECIASUAVE 33

Especia::Especia(int material, Config &config): Terreno(material) {
	if (material == 33) {
		cant_especia_actual = config["Especia Debil"].
		get("cantidad_especia", 0).asInt();
	} else {
		cant_especia_actual = config["Especia Fuerte"].
		get("cantidad_especia", 0).asInt();
	}
}

int Especia::sacar_especia(int cantidad) {
	if ((cant_especia_actual - cantidad) <= 0) {
		cant_especia_actual = 0;
		return cant_especia_actual;
	} else {
		cant_especia_actual -= cantidad;
		return cantidad;
	}
}

int Especia::obtener_cantidad_especia() {
	std::cout << " paso por cant especia de ESPECIA" << std::endl;
	return cant_especia_actual;
}

int Especia::reducir_especia(int cant_a_reducir) {
	std::cout << " paso por reducir especia de ESPECIA" << std::endl;
	cant_especia_actual -= cant_a_reducir;
	return cant_especia_actual;
}
