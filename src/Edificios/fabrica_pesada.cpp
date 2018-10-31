#include "fabrica_pesada.h"

#define ID_FABRICA_PESADA 5 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
FabricaPesada::FabricaPesada(int id, int id_duenio, std::pair<int, int> 
centro) : 
	Edificio(800, 1500, std::pair<int, int>(4, 4), 1500, id, id_duenio,
	400, 400, centro) {
		id_tipo = ID_FABRICA_PESADA;
	}

void FabricaPesada::crear_vehiculo_pesado(std::string nombre_vehiculo) {

}