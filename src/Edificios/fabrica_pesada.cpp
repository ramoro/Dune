#include "fabrica_pesada.h"

#define ID_FABRICA_PESADA 5 //para usarlo en el protocolo

FabricaPesada::FabricaPesada(int id, int id_duenio, std::pair<int, int> 
centro, Root &root) : 
	Edificio(root["FabricaPesada"].get("aporte_energetico", 0).asInt(),
	 root["FabricaPesada"].get("costo", 0).asInt(),
	 root["FabricaPesada"].get("puntos_estructura", 0).asInt(),
	  id, id_duenio, root["FabricaPesada"].get("dimension_ancho", 0).asInt(),
	   root["FabricaPesada"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = ID_FABRICA_PESADA;
	}

bool FabricaPesada::agregar_al_juego(Mapa &mapa, Jugador &jugador, 
int id_edificio, int id_tipo_edificio) {
	return Edificio::agregar(mapa, jugador, id_edificio, 
	id_tipo_edificio);
}

void FabricaPesada::destruir(Mapa &mapa, Jugador &jugador) {
	Edificio::eliminar(mapa, jugador);
}