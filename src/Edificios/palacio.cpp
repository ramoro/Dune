#include "palacio.h"

#define ID_PALACIO 7 //para usarlo en el protocolo
#define DESTRUIDO -1

Palacio::Palacio(int id, int id_duenio, std::pair<int, int> centro,
 Config &config) : 
	Edificio(config["Palacio"].get("aporte_energetico", 0).asInt(),
	 config["Palacio"].get("costo", 0).asInt(),
	 config["Palacio"].get("puntos_estructura", 0).asInt(),
	  id, id_duenio, config["Palacio"].get("dimension_ancho", 0).asInt(),
	   config["Palacio"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = ID_PALACIO;
	}

bool Palacio::agregar_al_juego(Mapa &mapa, Jugador &jugador, int id_edificio, 
int id_tipo_edificio) {
	return Edificio::agregar(mapa, jugador, id_edificio, 
	id_tipo_edificio);
}

void Palacio::actualizar_existencia(Jugador &jugador) {
	if (estado == DESTRUIDO) {
		Edificio::serializar_mensaje_muerte();
	}
}