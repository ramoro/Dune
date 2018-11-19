#include "unidad_infanteria.h"

#define OBJETO_MUERTO -1

UnidadInfanteria::UnidadInfanteria(int rango, int velocidad, 
double tiempo_creacion, int costo_dinero, int vida, 
int id, int id_duenio, int base, int altura, std::pair<int, int> 
centro): UnidadMovible(rango, velocidad, tiempo_creacion, costo_dinero,
vida, id, id_duenio, base, altura, centro) {}

int UnidadInfanteria::daniar(UnidadMovible* unidad_atacante) {
	int danio = unidad_atacante->pedir_danio("infanteria");
	return ObjetoDune::reducir_vida(danio);
}