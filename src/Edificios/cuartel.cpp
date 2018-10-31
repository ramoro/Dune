#include "cuartel.h"

#define CUARTEL 6 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Cuartel::Cuartel(int id, int id_duenio, std::pair<int, int> centro) :
	Edificio(100, 300, std::pair<int, int>(3, 2), 300, id, id_duenio,
	300, 200, centro) {
		id_tipo = CUARTEL;
	}

void Cuartel::crear_infanteria(std::string nombre_infanteria) {

}
