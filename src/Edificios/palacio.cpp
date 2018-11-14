#include "palacio.h"

#define ID_PALACIO 7 //para usarlo en el protocolo

Palacio::Palacio(int id, int id_duenio, std::pair<int, int> centro, Root &root) : 
	Edificio(root["Palacio"].get("aporte_energetico", 0).asInt(),
	 root["Palacio"].get("costo", 0).asInt(),
	 root["Palacio"].get("puntos_estructura", 0).asInt(),
	  id, id_duenio, root["Palacio"].get("dimension_ancho", 0).asInt(),
	   root["Palacio"].get("dimension_alto", 0).asInt(), centro) {
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