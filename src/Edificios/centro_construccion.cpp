#include "centro_construccion.h"

#define ID_CENTRO_CONSTRUCCION 0 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
CentroConstruccion::CentroConstruccion(int id, int id_duenio,
std::pair<int, int> centro) : 
	Edificio(0, 0, 3000, id, id_duenio, 3, 3, centro) {
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