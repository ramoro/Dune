#include "devastador.h"
#include "../Armas/canion_plasma.h"

#define ID_DEVASTADOR 9 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Devastador::Devastador(int id, int id_duenio, std::pair<int, int> centro) : 
	UnidadMovible(4, 12, 5, 400, 400, id, id_duenio, 50, 50, centro) {
		id_tipo = ID_DEVASTADOR;
		danio_explosion = 20;
		CanionPlasma canion_plasma;
		armas.push_back(CanionPlasma(canion_plasma));
	}
