#include "infanteria_pesada.h"
#include "../Armas/lanza_misiles.h"

#define ID_INFANTERIA_PESADA 1 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
InfanteriaPesada::InfanteriaPesada() : 
	UnidadMovible(3, 12, 1.3, 70, 80) {
		id_tipo = ID_INFANTERIA_PESADA;
		LanzaMisiles lanza_misiles;
		lanza_misiles.push_back(LanzaMisiles(lanza_misiles));
	}
	