#include "centro_construccion.h"

#define ID_CENTRO_CONSTRUCCION 0 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
CentroConstruccion::CentroConstruccion(int id, int id_duenio,
std::pair<int, int> centro, Root &root) : 
	Edificio(root["CentroConstruccion"].get("energia_requerida", 0).asInt(),
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

void CentroConstruccion::destruir(Mapa &mapa, Jugador &jugador) {
	Edificio::eliminar(mapa, jugador);
}