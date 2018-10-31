#include "trampa_aire.h"

#define ID_TRAMPA_AIRE 1 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
TrampaAire::TrampaAire(int id, int id_duenio, std::pair<int, int> centro) : 
	Edificio(0, 800, std::pair<int, int>(3, 3), 500, id, id_duenio, 300, 300, 
	centro) {
		energia_generada = 500;
		id_tipo = ID_TRAMPA_AIRE;
	}