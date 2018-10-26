#include "especia.h"

Especia::Especia(std::string material): Terreno(material) {}

int Especia::sacar_especia(int cantidad) {
	if ((cant_especia_actual - cantidad) <= 0) {
		cant_especia_actual = 0;
		return cant_especia_actual;
	} else {
		cant_especia_actual -= cantidad;
		return cantidad;
	}
}