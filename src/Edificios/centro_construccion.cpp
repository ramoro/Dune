#include "centro_construccion.h"

#define ID_CENTRO_CONSTRUCCION 0 //para usarlo en el protocolo
#define DESTRUIDO -1

CentroConstruccion::CentroConstruccion(int id, int id_duenio,
std::pair<int, int> centro, Root &root) : 
	Edificio(root["CentroConstruccion"].get("aporte_energetico", 0).asInt(),
	 root["CentroConstruccion"].get("costo", 0).asInt(),
	 root["CentroConstruccion"].get("puntos_estructura", 0).asInt(),
	  id, id_duenio, root["CentroConstruccion"].get("dimension_ancho", 0).asInt(),
	   root["CentroConstruccion"].get("dimension_alto", 0).asInt(), centro) {
		id_tipo = ID_CENTRO_CONSTRUCCION;
	}

bool CentroConstruccion::agregar_al_juego(Mapa &mapa, Jugador &jugador, int id_edificio, 
int id_tipo_edificio) {
	return Edificio::agregar(mapa, jugador, id_edificio, 
	id_tipo_edificio);
}

void CentroConstruccion::actualizar_existencia(Jugador &jugador) {
	if (estado == DESTRUIDO) {
		Edificio::serializar_mensaje_muerte();
		Edificio::serializar_mensaje_perdio_jugador();
	}
}