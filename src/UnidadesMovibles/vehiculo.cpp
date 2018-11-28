#include "vehiculo.h"

#define CODIGO_PRECIPICIO 35
#define CODIGO_CIMA 34

Vehiculo::Vehiculo(int rango, int velocidad, 
float tiempo_creacion, int costo_dinero, int vida, 
int id, int id_duenio, int base, int altura, std::pair<int, int> 
centro): UnidadMovible(rango, velocidad, tiempo_creacion, costo_dinero,
vida, id, id_duenio, base, altura, centro) {
}

int Vehiculo::daniar(UnidadMovible* unidad_atacante, int tiempo_transcurrido) {
	int danio_recibido = unidad_atacante->pedir_danio("vehiculo", 
	tiempo_transcurrido);
	return ObjetoDune::reducir_vida(danio_recibido);
}

bool Vehiculo::es_terreno_valido(int terreno){
	if (terreno == CODIGO_PRECIPICIO || terreno == CODIGO_CIMA)
		return false;
	return true;
}