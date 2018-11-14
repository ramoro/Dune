#include "refineria.h"

#define ID_REFINERIA 2 //para usarlo en el protocolo

Refineria::Refineria(int id, int id_duenio, std::pair<int, int> centro,
 Root &root) : 
	Edificio(root["Refineria"].get("aporte_energetico", 0).asInt(),
	 root["Refineria"].get("costo", 0).asInt(),
	 root["Refineria"].get("puntos_estructura", 0).asInt(),
	  id, id_duenio, root["Refineria"].get("dimension_ancho", 0).asInt(),
	   root["Refineria"].get("dimension_alto", 0).asInt(), centro) {
		capacidad =  root["Refineria"].get("capacidad", 0).asInt();
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