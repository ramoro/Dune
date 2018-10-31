#include "tanque.h"
#include "../Armas/canion.h"

#define ID_TANQUE 6 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Tanque::Tanque(int id, int id_duenio, std::pair<int, int> centro) : 
	UnidadMovible(4, 40, 4, 400, 30, id, id_duenio, 50, 50, centro) {
		id_tipo = ID_TANQUE;
		Canion canion;
		armas.push_back(Canion(canion));
	}