#include "refineria.h"

#define ID_REFINERIA 2 //para usarlo en el protocolo

//DATOS DE INICIALIZACION HARCODEADOS (VAN A VENIR DEL ARCHIVO CONFIG)
Refineria::Refineria(int id, int id_duenio, std::pair<int, int> centro) : 
	Edificio(-400, 500, 500, id, id_duenio, 300, 300, centro) {
		capacidad = 5000;
		id_tipo = ID_REFINERIA;
	}

bool Refineria::agregar_al_juego(Mapa &mapa, Jugador &jugador, int id_edificio, 
int id_tipo_edificio) {
	bool agregado = Edificio::agregar(mapa, jugador, id_edificio, 
	id_tipo_edificio);
	if (agregado) {
		jugador.aumentar_capacidad_especia(capacidad);
	}
	return true;
}

void Refineria::destruir(Mapa &mapa, Jugador &jugador) {
	jugador.reducir_capacidad_especia(capacidad);
	Edificio::eliminar(mapa, jugador);
}

/*int Refineria::depositar_especia(int cantidad_especia) {
	int espacio_restante = capacidad - cantidad_especia;
	if (espacio_restante >= 0) return 0;
	else return (cantidad_especia - capacidad);
}*/