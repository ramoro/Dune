#include "fabrica_ligera.h"

#define ID_FABRICA_LIGERA 4 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
FabricaLigera::FabricaLigera(int id, int id_duenio, std::pair<int, int> 
centro) : 
	Edificio(500, 800, std::pair<int, int>(3, 3), 500, id, id_duenio,
	5, 4, centro) {
		id_tipo = ID_FABRICA_LIGERA;
	}