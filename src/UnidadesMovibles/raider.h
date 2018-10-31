#ifndef RAIDER_H
#define RAIDER_H

#include "unidad_movible.h"
#include <utility>

/*Clase que representa una unidad de un raider en el mundo de Dune.
Es un vehiculo similar a un Trike pero mucho mas rapido.*/
class Raider: public UnidadMovible {
	public:
		/*Constructor de la clase.*/
		Raider(int id, int id_duenio, std::pair<int, int> centro);
};

#endif

