#include "trampa_aire.h"

#define ID_TRAMPA_AIRE 1 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
TrampaAire::TrampaAire(int id, int id_duenio, std::pair<int, int> centro) : 
	Edificio(500, 800, 500, id, id_duenio, 1, 1, centro) {
		id_tipo = ID_TRAMPA_AIRE;
	}

bool TrampaAire::agregar_al_juego(Mapa &mapa, Jugador &jugador, 
int id_edificio, int id_tipo_edificio) {
	return Edificio::agregar(mapa, jugador, id_edificio,
	id_tipo_edificio);
}

void TrampaAire::destruir(Mapa &mapa, Jugador &jugador) {
	Edificio::eliminar(mapa, jugador);
}