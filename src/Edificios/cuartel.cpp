#include "cuartel.h"

#define CUARTEL 6 //para usarlo en el protocolo
#define DESTRUIDO -1

Cuartel::Cuartel(int id, int id_duenio, std::pair<int, int> centro,
 Config &config) :
	Edificio(config["Cuartel"].get("aporte_energetico", 0).asInt(),
	 config["Cuartel"].get("costo", 0).asInt(),
	 config["Cuartel"].get("puntos_estructura", 0).asInt(),
	 id, id_duenio, config["Cuartel"].get("dimension_ancho", 0).asInt(),
	 config["Cuartel"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = CUARTEL;

	}

bool Cuartel::agregar_al_juego(Mapa &mapa, Jugador &jugador, int id_edificio, 
int id_tipo_edificio) {
	return Edificio::agregar(mapa, jugador, id_edificio, 
	id_tipo_edificio);
}

void Cuartel::actualizar_existencia(Jugador &jugador) {
	if (estado == DESTRUIDO) {
		Edificio::serializar_mensaje_muerte();
	}
}