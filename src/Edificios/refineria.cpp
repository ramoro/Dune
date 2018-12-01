#include "refineria.h"

#define ID_REFINERIA 2 //para usarlo en el protocolo
#define DESTRUIDO -1

Refineria::Refineria(int id, int id_duenio, std::pair<int, int> centro,
 Config &config) : 
	Edificio(config["Refineria"].get("aporte_energetico", 0).asInt(),
	 config["Refineria"].get("costo", 0).asInt(),
	 config["Refineria"].get("puntos_estructura", 0).asInt(),
	  id, id_duenio, config["Refineria"].get("dimension_ancho", 0).asInt(),
	   config["Refineria"].get("dimension_alto", 0).asInt(), centro) {
		capacidad =  config["Refineria"].get("capacidad", 0).asInt();
		id_tipo = ID_REFINERIA;
		cantidad_especia = 0;
	}

bool Refineria::agregar_al_juego(Mapa &mapa, Jugador &jugador, int id_edificio, 
int id_tipo_edificio) {
	bool agregado = Edificio::agregar(mapa, jugador, id_edificio, 
	id_tipo_edificio);
	if (agregado) {
		jugador.aumentar_capacidad_especia(capacidad);
		mapa.agregar_refineria(this);
	}
	return agregado;
}

void Refineria::actualizar_existencia(Jugador &jugador) {
	if (estado == DESTRUIDO) {
		jugador.reducir_capacidad_especia(capacidad);
		Edificio::serializar_mensaje_muerte();
	}
}

void Refineria::agregar_especia(int especia) {
	//std::cout << "Refineria::agregar_especia "<< especia << std::endl;
	cantidad_especia += especia;
}

void Refineria::reducir_especia(int especia) {
	cantidad_especia -= especia;
}

int Refineria::obtener_especia() {
	return cantidad_especia;
}