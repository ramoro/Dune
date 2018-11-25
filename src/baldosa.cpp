#include "baldosa.h"
#include "UnidadesMovibles/cosechadora.h"
#include "mensaje_protocolo.h"

#define VACIA 0
#define OCUPADA 1

Baldosa::Baldosa(int estado, Terreno terreno, int id, 
std::pair<int, int> posicion): ObjetoDune(terreno.obtener_cantidad_especia(),
0, id, -1, 1, 1, posicion), estado(estado), 
terreno(terreno) {}

bool Baldosa::poner_objeto(ObjetoDune* objeto_dune) {
	if (estado == OCUPADA) {
		return false;
	} else {
		objeto = objeto_dune;
		estado = OCUPADA;
		return true;
	}
}

std::string Baldosa::obtener_terreno() {
	return terreno.obtener_nombre_material();
}

void Baldosa::sacar_objeto() {
	objeto = NULL;
	estado = VACIA;
}

bool Baldosa::esta_ocupada() {
	if(estado == OCUPADA) return true;
	return false;
}

int Baldosa::obtener_id_objeto_contenido() {
	return objeto->pedir_id();
}

void Baldosa::marcar_como_ocupada() {
	estado = OCUPADA;
}

void Baldosa::marcar_como_desocupada() {
	estado = VACIA;
}

int Baldosa::remover_especia(Cosechadora* unidad_atacante) {
	return terreno.reducir_especia(unidad_atacante->
	obtener_extraccion_especia());
}

void Baldosa::matar() {
	ObjetoDune::mensaje_muerte();
	fuera_de_juego = true;
}
