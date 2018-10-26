#include "cosechadora.h"

#define ID_COSECHADORA 10 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Cosechadora::Cosechadora() : 
	UnidadMovible(0, 12, 3, 300, 600) {
		id_tipo = ID_COSECHADORA;
	}
	