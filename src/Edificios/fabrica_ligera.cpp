#include "fabrica_ligera.h"

#define ID_FABRICA_LIGERA 4 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
FabricaLigera::FabricaLigera(int id, int id_duenio, std::pair<int, int> 
centro) : 
	Edificio(-500, 800, 500, id, id_duenio, 300, 300, centro) {
		id_tipo = ID_FABRICA_LIGERA;
	}

bool FabricaLigera::agregar_al_juego(Mapa &mapa, Jugador &jugador, 
int id_edificio, int id_tipo_edificio) {
	return Edificio::agregar(mapa, jugador, id_edificio, 
	id_tipo_edificio);
}

void FabricaLigera::destruir(Mapa &mapa, Jugador &jugador) {
	Edificio::eliminar(mapa, jugador);
}