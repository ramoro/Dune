#include "tanque.h"
#include "../Armas/canion.h"

#define ID_TANQUE 6 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Tanque::Tanque() : 
	UnidadMovible(4, 40, 4, 400, 30) {
		id_tipo = ID_TANQUE;
		Canion canion;
		armas.push_back(Canion(canion));
	}
	