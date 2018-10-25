#include "fabrica_ligera.h"
#include <utility>

#define ID_FABRICA_LIGERA 4 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
FabricaLigera::FabricaLigera() : 
	Edificio(500, 800, std::pair<int, int>(3, 3), 500) {
		id_tipo = ID_FABRICA_LIGERA;
	}