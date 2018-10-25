#include "fabrica_pesada.h"
#include <utility>

#define ID_FABRICA_PESADA 5 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
FabricaPesada::FabricaPesada() : 
	Edificio(800, 1500, std::pair<int, int>(4, 4), 1500) {
		id_tipo = ID_FABRICA_PESADA;
	}

void FabricaPesada::crear_vehiculo_pesado(std::string nombre_vehiculo) {

}