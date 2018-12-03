#include "unidad_infanteria.h"

#define OBJETO_MUERTO -1
#define PRECIPICIO 35

UnidadInfanteria::UnidadInfanteria(int rango, int velocidad, 
double tiempo_creacion, int costo_dinero, int vida, 
int id, int id_duenio, int base, int altura, std::pair<int, int> 
centro): UnidadMovible(rango, velocidad, tiempo_creacion, costo_dinero,
vida, id, id_duenio, base, altura, centro) {
}

int UnidadInfanteria::daniar(UnidadMovible* unidad_atacante, 
int tiempo_transcurrido) {
	int danio_recibido = unidad_atacante->pedir_danio("infanteria",
	tiempo_transcurrido);
	return ObjetoDune::reducir_vida(danio_recibido);
}

int UnidadInfanteria::daniar_devastador(UnidadMovible* unidad_atacante) {
	int danio_recibido = unidad_atacante->pedir_danio_explosion("infanteria");
	return ObjetoDune::reducir_vida(danio_recibido);
}

bool UnidadInfanteria::es_terreno_valido(int terreno){
	if (terreno == PRECIPICIO)
		return false;
	return true;
}