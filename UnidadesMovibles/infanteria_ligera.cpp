#include "infanteria_ligera.h"
#include "../Armas/rifle_asalto.h"

#define ID_INFANTERIA_LIGERA 0 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
InfanteriaLigera::InfanteriaLigera() : 
	UnidadMovible(3, 16, 1, 50, 50) {
		id_tipo = ID_INFANTERIA_LIGERA;
		RifleAsalto rifle;
		rile.push_back(RifleAsalto(rifle));
	}
	