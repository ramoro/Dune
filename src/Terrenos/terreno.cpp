#include "terreno.h"
#include <iostream>

#define CODIGO_ESPECIAFUERTE 32
#define CODIGO_ESPECIASUAVE 33

Terreno::Terreno(int material, Config &config): material(material) {
	if (material == CODIGO_ESPECIASUAVE) {
		cant_especia_actual = config["Especia Suave"].
		get("cantidad_especia", 0).asInt();
	} else if(material == CODIGO_ESPECIAFUERTE) {
		cant_especia_actual = config["Especia Fuerte"].
		get("cantidad_especia", 0).asInt();
	} else {
		cant_especia_actual = 0;
	}
}

int Terreno::obtener_id_material() {
	return material;
}

int Terreno::reducir_especia(int cantidad) {
	int especia_sobrante = cant_especia_actual - cantidad;
	if (especia_sobrante < 0) {
		cant_especia_actual = 0;
	} 
	return especia_sobrante;
}

int Terreno::obtener_cantidad_especia() {
	return cant_especia_actual;
}
