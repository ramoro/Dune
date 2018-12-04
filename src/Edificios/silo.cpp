#include "silo.h"

#define ID_SILO 3 //para usarlo en el protocolo
#define DESTRUIDO -1

Silo::Silo(int id, int id_duenio, std::pair<int, int> centro, Config &config) : 
	Edificio(config["Silo"].get("aporte_energetico", 0).asInt(),
	 config["Silo"].get("costo", 0).asInt(),
	 config["Silo"].get("puntos_estructura", 0).asInt(),
	  id, id_duenio, config["Silo"].get("dimension_ancho", 0).asInt()
	 *config["cant_pixeles_por_baldosa"].asInt(),
	   config["Silo"].get("dimension_alto", 0).asInt()
	 *config["cant_pixeles_por_baldosa"].asInt(), centro) {
		capacidad = config["Silo"].get("capacidad", 0).asInt();
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

void Silo::actualizar_existencia(Jugador &jugador) {
	if (estado == DESTRUIDO) {
		jugador.reducir_capacidad_especia(capacidad);
		Edificio::serializar_mensaje_muerte();
	}
}
/*int Silo::depositar_especia(int cantidad_especia) {
	int espacio_restante = capacidad - cantidad_especia;
	if (espacio_restante >= 0) return 0;
	else return (cantidad_especia - capacidad);
}*/