#include "unidad_infanteria.h"

#define OBJETO_MUERTO -1
#define PRECIPICIO 35
#define SEGUNDO_EN_MILIS 1000

UnidadInfanteria::UnidadInfanteria(int rango, int velocidad, 
double tiempo_creacion, int costo_dinero, int vida, 
int id, int id_duenio, int base, int altura, std::pair<int, int> 
centro): UnidadMovible(rango, velocidad, tiempo_creacion, costo_dinero,
vida, id, id_duenio, base, altura, centro) {
	contador_seg = 0;
}

int UnidadInfanteria::daniar(UnidadMovible* unidad_atacante, 
int tiempo_transcurrido) {
	int danio_recibido = 0;
	contador_seg += tiempo_transcurrido;
	/*if (contador_seg >= SEGUNDO_EN_MILIS) {
		contador_seg -= SEGUNDO_EN_MILIS;
		danio_recibido = unidad_atacante->pedir_danio("infanteria");
		std::cout << "danio recibido: " << danio_recibido << std::endl;
	}*/
	danio_recibido = unidad_atacante->pedir_danio("infanteria");
	return ObjetoDune::reducir_vida(danio_recibido);
}

bool UnidadInfanteria::es_terreno_valido(int terreno){
	if (terreno == PRECIPICIO)
		return false;
	return true;
}