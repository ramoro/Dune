#include "refineria.h"
#include <utility>

#define ID_REFINERIA 2 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Refineria::Refineria() : 
	Edificio(400, 500, std::pair<int, int>(3, 3), 500) {
		capacidad = 5000;
		id_tipo = ID_REFINERIA;
	}

int Refineria::depositar_especia(int cantidad_especia) {
	int espacio_restante = capacidad - cantidad_especia;
	if (espacio_restante >= 0) return 0;
	else return (cantidad_especia - capacidad);
}