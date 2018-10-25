#include "centro_construccion.h"
#include <utility>

#define ID_CENTRO_CONSTRUCCION 0 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
CentroConstruccion::CentroConstruccion() : 
	Edificio(0, 0, std::pair<int, int>(3, 3), 3000) {
		id_tipo = ID_CENTRO_CONSTRUCCION;
	}