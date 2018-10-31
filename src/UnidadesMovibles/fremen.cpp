#include "fremen.h"
#include "../Armas/lanza_misiles.h"
#include "../Armas/rifle_asalto.h"

#define ID_FREMEN 2 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Fremen::Fremen(int id, int id_duenio, std::pair<int, int> centro) : 
	UnidadMovible(3, 20, 2, 100, 50, id, id_duenio, 50, 50, centro) {
		id_tipo = ID_FREMEN;
		RifleAsalto rifle_asalto;
		LanzaMisiles lanza_misiles;
		armas.push_back(RifleAsalto(rifle_asalto));
		armas.push_back(LanzaMisiles(lanza_misiles));
	}
