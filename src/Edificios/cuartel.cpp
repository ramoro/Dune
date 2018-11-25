#include "cuartel.h"

#define DESTRUIDO -1
#define CUARTELATREIDES 6
#define CUARTELHARKONNEN 7
#define CUARTELORDOS 8

Cuartel::Cuartel(int id, int id_duenio, std::pair<int, int> centro,
 Config &config, int  id_tipo_edificio) :
	Edificio(config["Cuartel"].get("aporte_energetico", 0).asInt(),
	 config["Cuartel"].get("costo", 0).asInt(),
	 config["Cuartel"].get("puntos_estructura", 0).asInt(),
	 id, id_duenio, config["Cuartel"].get("dimension_ancho", 0).asInt(),
	 config["Cuartel"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = id_tipo_edificio;
	}

bool Cuartel::agregar_al_juego(Mapa &mapa, Jugador &jugador, int id_edificio, 
int id_tipo_edificio) {
	if (jugador.obtener_casa() == "harkonnen" && 
		id_tipo_edificio == CUARTELHARKONNEN){
		return Edificio::agregar(mapa, jugador, id_edificio,
		 id_tipo_edificio);
	} else if (jugador.obtener_casa() == "ordos" && 
		id_tipo_edificio == CUARTELORDOS){
		return Edificio::agregar(mapa, jugador, id_edificio,
		 id_tipo_edificio);
	} else if (jugador.obtener_casa() == "atreides" && 
		id_tipo_edificio == CUARTELATREIDES){
		return Edificio::agregar(mapa, jugador, id_edificio,
		 id_tipo_edificio);
	} 
	return false;
}

void Cuartel::actualizar_existencia(Jugador &jugador) {
	if (estado == DESTRUIDO) {
		Edificio::serializar_mensaje_muerte();
	}
}