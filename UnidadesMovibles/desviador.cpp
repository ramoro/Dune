#include "desviador.h"
#include "../Armas/lanza_misiles.h"

#define ID_DESVIADOR 8 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Desviador::Desviador() : 
	UnidadMovible(5, 12, 4, 400, 300) {
		id_tipo = ID_DESVIADOR;
		LanzaMisiles lanza_misiles;
		armas.push_back(LanzaMisiles(lanza_misiles));
	}
	