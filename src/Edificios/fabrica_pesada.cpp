#include "fabrica_pesada.h"

#define ID_FABRICA_PESADA 5 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
FabricaPesada::FabricaPesada(int id, int id_duenio, std::pair<int, int> 
centro) : 
	Edificio(-800, 1500, 1, id, id_duenio, 1, 1, centro) {
		id_tipo = ID_FABRICA_PESADA;
	}

bool FabricaPesada::agregar_al_juego(Mapa &mapa, Jugador &jugador, 
int id_edificio, int id_tipo_edificio) {
	return Edificio::agregar(mapa, jugador, id_edificio, 
	id_tipo_edificio);
}

void FabricaPesada::destruir(Mapa &mapa, Jugador &jugador) {
	Edificio::eliminar(mapa, jugador);
}