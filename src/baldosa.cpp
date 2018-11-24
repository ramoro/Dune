#include "baldosa.h"

#define VACIA 0
#define OCUPADA 1

Baldosa::Baldosa(int estado, Terreno terreno,int &id): estado(estado), 
terreno(terreno) , id(id++){}

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