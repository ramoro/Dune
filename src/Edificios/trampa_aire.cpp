#include "trampa_aire.h"

#define ID_TRAMPA_AIRE 1 //para usarlo en el protocolo
#define DESTRUIDO -1

TrampaAire::TrampaAire(int id, int id_duenio, std::pair<int, int> centro,
 Config &config) : 
	Edificio(config["TrampaAire"].get("aporte_energetico", 0).asInt(),
	 config["TrampaAire"].get("costo", 0).asInt(),
	 config["TrampaAire"].get("puntos_estructura", 0).asInt(),
	  id, id_duenio, config["TrampaAire"].get("dimension_ancho", 0).asInt()
	 *config["cant_pixeles_por_baldosa"].asInt(),
	   config["TrampaAire"].get("dimension_alto", 0).asInt()
	 *config["cant_pixeles_por_baldosa"].asInt(), centro) {
		id_tipo = ID_TRAMPA_AIRE;
	}

bool TrampaAire::agregar_al_juego(Mapa &mapa, Jugador &jugador, 
int id_edificio, int id_tipo_edificio) {
	return Edificio::agregar(mapa, jugador, id_edificio,
	id_tipo_edificio);
}

void TrampaAire::actualizar_existencia(Jugador &jugador) {
	if (estado == DESTRUIDO) {
		Edificio::serializar_mensaje_muerte();
	}
}