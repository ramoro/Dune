#include "unidad_movible.h"
#include <stdlib.h> 

UnidadMovible::UnidadMovible(int rango, int velocidad, 
float tiempo_creacion, int costo_dinero, int vida, int id, int id_duenio,
int base, int altura, std::pair<int, int> centro) :
	ObjetoDune(vida, costo_dinero, id, id_duenio, base, altura, centro),
	rango(rango), velocidad(velocidad), tiempo_creacion(tiempo_creacion){}

int UnidadMovible::pedir_danio(std::string objetivo) {
	int arma_seleccionada = rand() % armas.size();
	return armas[arma_seleccionada].obtener_danio(objetivo);
}

/*UnidadMovible::UnidadMovible(UnidadMovible&& other){
	rango= other.rango;
	velocidad = other.velocidad;
	tiempo_creacion = other.tiempo_creacion;
	vida = other.vida;
	costo_dinero = other.costo_dinero;
	armas = other.armas;
}*/