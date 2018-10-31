#ifndef TANQUE_H
#define TANQUE_H

#include "unidad_movible.h"
#include <utility>

/*Clase que representa una unidad de un tanque comun en el mundo de Dune.
Es un vehiculo de ataque versatil. Unidad de combate por excelencia.*/ 
class Tanque: public UnidadMovible {
	public:
		/*Constructor de la clase.*/
		Tanque(int id, int id_duenio, std::pair<int, int> centro);

};

#endif

