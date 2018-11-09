#include "silo.h"

#define ID_SILO 3 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Silo::Silo(int id, int id_duenio, std::pair<int, int> centro, Root &root) : 
	Edificio(root["Silo"].get("energia_requerida", 0).asInt(),
	 root["Silo"].get("costo", 0).asInt(),
	 root["Silo"].get("puntos_estructura", 0).asInt(),
	  id, id_duenio, root["Silo"].get("dimension_ancho", 0).asInt(),
	   root["Silo"].get("dimension_alto", 0).asInt(), centro) {
		capacidad = root["Silo"].get("capacidad", 0).asInt();
		id_tipo = ID_SILO;
	}


bool Silo::agregar_al_juego(Mapa &mapa, Jugador &jugador, int id_edificio, 
int id_tipo_edificio) {
	bool agregado;
	agregado = Edificio::agregar(mapa, jugador, id_edificio, 
	id_tipo_edificio);
	if (agregado) {
		jugador.aumentar_capacidad_especia(capacidad);
	}
	return agregado;
}

void Silo::destruir(Mapa &mapa, Jugador &jugador) {
	jugador.reducir_capacidad_especia(capacidad);
	Edificio::eliminar(mapa, jugador);
}
/*int Silo::depositar_especia(int cantidad_especia) {
	int espacio_restante = capacidad - cantidad_especia;
	if (espacio_restante >= 0) return 0;
	else return (cantidad_especia - capacidad);
}*/