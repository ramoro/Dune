#include "objeto_dune.h"

ObjetoDune::ObjetoDune(int vida, int costo): vida(vida), costo_dinero(costo){}

int ObjetoDune::reducir_vida(int danio) {
	vida -= danio;
	return vida;
} 

int ObjetoDune::obtener_costo() {
	return costo_dinero;
}

int ObjetoDune::pedir_id_tipo() {
	return id_tipo;
}
