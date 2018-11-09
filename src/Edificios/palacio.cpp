#include "palacio.h"

#define ID_PALACIO 7 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Palacio::Palacio(int id, int id_duenio, std::pair<int, int> centro) : 
	Edificio(800, 2000, 1, id, id_duenio, 1, 1, centro) {
		id_tipo = ID_PALACIO;
	}

bool Palacio::agregar_al_juego(Mapa &mapa, Jugador &jugador, int id_edificio, 
int id_tipo_edificio) {
	return Edificio::agregar(mapa, jugador, id_edificio, 
	id_tipo_edificio);
}

void Palacio::destruir(Mapa &mapa, Jugador &jugador) {
	Edificio::eliminar(mapa, jugador);
}