#include "infanteria_ligera.h"
#include "../Armas/rifle_asalto.h"

#define ID_INFANTERIA_LIGERA 0 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
InfanteriaLigera::InfanteriaLigera(int id, int id_duenio, std::pair<int, int>
centro) : 
	UnidadMovible(3, 16, 1, 50, 50, id, id_duenio, 50, 50, centro) {
		id_tipo = ID_INFANTERIA_LIGERA;
		RifleAsalto rifle;
		armas.push_back(RifleAsalto(rifle));
	}
