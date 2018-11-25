#include "terreno.h"
#include <iostream>

Terreno::Terreno(std::string material, Config &config): material(material) {
	if (material == "especia debil") {
		cant_especia_actual = config["Especia Suave"].
		get("cantidad_especia", 0).asInt();
	} else if(material == "especia fuerte") {
		cant_especia_actual = config["Especia Fuerte"].
		get("cantidad_especia", 0).asInt();
	} else {
		cant_especia_actual = 0;
	}
}

std::string Terreno::obtener_nombre_material() {
	return material;
}

int Terreno::sacar_especia(int cantidad) {
	if ((cant_especia_actual - cantidad) <= 0) {
		cant_especia_actual = 0;
		return cant_especia_actual;
	} else {
		cant_especia_actual -= cantidad;
		return cantidad;
	}
}

int Terreno::obtener_cantidad_especia() {
	return cant_especia_actual;
}

int Terreno::reducir_especia(int cant_a_reducir) {
	cant_especia_actual -= cant_a_reducir;
	return cant_especia_actual;
}