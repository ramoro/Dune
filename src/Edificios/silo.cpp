#include "silo.h"

#define ID_SILO 3 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Silo::Silo(int id, int id_duenio, std::pair<int, int> centro) : 
	Edificio(100, 200, std::pair<int, int>(1, 1), 1000, id, id_duenio, 100,
	100, centro) {
		capacidad = 1000;
		id_tipo = ID_SILO;
	}

int Silo::depositar_especia(int cantidad_especia) {
	int espacio_restante = capacidad - cantidad_especia;
	if (espacio_restante >= 0) return 0;
	else return (cantidad_especia - capacidad);
}