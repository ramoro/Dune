#include "raider.h"
#include "../Armas/canion_22mm.h"

#define ID_RAIDER 5 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Raider::Raider() : 
	UnidadMovible(4, 84, 2, 100, 80) {
		id_tipo = ID_RAIDER;
		Canion22mm canion22mm;
		canion22mm.push_back(Canion22mm(canion22mm));
	}
	