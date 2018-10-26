#include "cuartel.h"
#include <utility>

#define CUARTEL 6 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Cuartel::Cuartel() :
	Edificio(100, 300, std::pair<int, int>(3, 2), 300) {
		id_tipo = CUARTEL;
	}

void Cuartel::crear_infanteria(std::string nombre_infanteria) {

}
