#include "fabrica_ligera.h"

#define ID_FABRICA_LIGERA 4 //para usarlo en el protocolo
#define DESTRUIDO -1

FabricaLigera::FabricaLigera(int id, int id_duenio, std::pair<int, int> 
centro,Config &config) : 
	Edificio(config["FabricaLigera"].get("aporte_energetico", 0).asInt(),
	 config["FabricaLigera"].get("costo", 0).asInt(),
	 config["FabricaLigera"].get("puntos_estructura", 0).asInt(),
	  id, id_duenio, config["FabricaLigera"].get("dimension_ancho", 0).asInt()
	 *config["cant_pixeles_por_baldosa"].asInt(),
	   config["FabricaLigera"].get("dimension_alto", 0).asInt()
	 *config["cant_pixeles_por_baldosa"].asInt(), centro) {
		id_tipo = ID_FABRICA_LIGERA;
	}

bool FabricaLigera::agregar_al_juego(Mapa &mapa, Jugador &jugador, 
int id_edificio, int id_tipo_edificio) {
	return Edificio::agregar(mapa, jugador, id_edificio, 
	id_tipo_edificio);
}

void FabricaLigera::actualizar_existencia(Jugador &jugador) {
	if (estado == DESTRUIDO) {
		Edificio::serializar_mensaje_muerte();
	}
}