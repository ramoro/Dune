#include "sardaukar.h"
#include "../Armas/rifle_asalto.h"
#include "../Armas/lanza_misiles.h"

#define ID_SARDAUKAR 3 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Sardaukar::Sardaukar(int id, int id_duenio, std::pair<int, int> centro) : 
	UnidadMovible(3, 12, 2, 100, 80, id, id_duenio, 50, 50, centro) {
		id_tipo = ID_SARDAUKAR;
		RifleAsalto rifle_asalto;
		LanzaMisiles lanza_misiles;
		armas.push_back(RifleAsalto(rifle_asalto));
		armas.push_back(LanzaMisiles(lanza_misiles));
	}