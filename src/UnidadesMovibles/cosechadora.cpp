#include "cosechadora.h"

#define ID_COSECHADORA 10 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Cosechadora::Cosechadora(int id, int id_duenio, std::pair<int, int> centro) : 
	UnidadMovible(0, 12, 3, 300, 600, id, id_duenio, 50, 50, centro) {
		id_tipo = ID_COSECHADORA;
	}

