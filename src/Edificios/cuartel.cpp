#include "cuartel.h"

#define CUARTEL 6 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Cuartel::Cuartel(int id, int id_duenio, std::pair<int, int> centro) :
	Edificio(-100, 300, 300, id, id_duenio, 3, 2, centro) {
		id_tipo = CUARTEL;
	}

bool Cuartel::agregar_al_juego(Mapa &mapa, Jugador &jugador, int id_edificio, 
int id_tipo_edificio) {
	return Edificio::agregar(mapa, jugador, id_edificio, 
	id_tipo_edificio);
}

void Cuartel::destruir(Mapa &mapa, Jugador &jugador) {
	Edificio::eliminar(mapa, jugador);
}