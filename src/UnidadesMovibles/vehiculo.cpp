#include "vehiculo.h"

Vehiculo::Vehiculo(int rango, int velocidad, 
float tiempo_creacion, int costo_dinero, int vida, 
int id, int id_duenio, int base, int altura, std::pair<int, int> 
centro): UnidadMovible(rango, velocidad, tiempo_creacion, costo_dinero,
vida, id, id_duenio, base, altura, centro) {}

int Vehiculo::daniar(UnidadMovible* unidad_atacante) {
	int danio = unidad_atacante->pedir_danio("vehiculo");
	return ObjetoDune::reducir_vida(danio);
}