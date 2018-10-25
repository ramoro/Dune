#include "trike.h"
#include "../Armas/rifle_asalto.h"

#define ID_TRIKE 4 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Trike::Trike() : 
	UnidadMovible(4, 64, 2, 100, 80) {
		id_tipo = ID_TRIKE;
		RifleAsalto rifle_asalto;
		armas.push_back(RifleAsalto(rifle_asalto));
	}
	