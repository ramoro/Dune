#include "centro_construccion.h"

#define ID_CENTRO_CONSTRUCCION 0 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
CentroConstruccion::CentroConstruccion(int id, int id_duenio,
std::pair<int, int> centro) : 
	Edificio(0, 0, std::pair<int, int>(3, 3), 3000, id, id_duenio,
	300, 300, centro) {
		id_tipo = ID_CENTRO_CONSTRUCCION;
	}