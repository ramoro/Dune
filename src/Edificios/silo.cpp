#include "silo.h"

#define ID_SILO 3 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Silo::Silo(int id, int id_duenio, std::pair<int, int> centro) : 
	Edificio(-100, 200, 1000, id, id_duenio, 100, 100, centro) {
		capacidad = 1000;
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