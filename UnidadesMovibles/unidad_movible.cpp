#include "unidad_movible.h"
#include <stdlib.h> 

UnidadMovible::UnidadMovible(int rango, int velocidad, 
float tiempo_creacion, int costo_dinero, int vida) :
	ObjetoDune(vida, costo_dinero), rango(rango), velocidad(velocidad),
	tiempo_creacion(tiempo_creacion){}

int UnidadMovible::pedir_danio(std::string objetivo) {
	int arma_seleccionada = rand() % armas.size();
	return armas[arma_seleccionada].obtener_danio(objetivo);
}