#include "palacio.h"
#include <utility>

#define ID_PALACIO 7 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Palacio::Palacio() : 
	Edificio(800, 2000, std::pair<int, int>(3, 3), 1000) {
		id_tipo = ID_PALACIO;
	}

void Palacio::crear_infanteria_avanzada(std::string nombre_infanteria) {

}