#include "devastador.h"
#include "../Armas/canion_plasma.h"

#define ID_DEVASTADOR 9 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Devastador::Devastador() : 
	UnidadMovible(4, 12, 5, 400, 400) {
		id_tipo = ID_DEVASTADOR;
		danio_explosion = 20;
		CanionPlasma canion_plasma;
		canion_plasma.push_back(CanionPlasma(canion_plasma));
	}
	