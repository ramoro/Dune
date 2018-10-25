#include "trampa_aire.h"

#define ID_TRAMPA_AIRE 1 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
TrampaAire::TrampaAire() : 
	Edificio(0, 800, std::pair<int, int>(3, 3), 500) {
		energia_generada = 500;
		id_tipo = ID_TRAMPA_AIRE;
	}