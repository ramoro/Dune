#ifndef TRIKE_H
#define TRIKE_H

#include "unidad_movible.h"
#include <utility>

/*Clase que representa una unidad de un trike en el mundo de Dune.
Es un vehiculo rapido armado conametralladoras.*/
class Trike: public UnidadMovible {
	public:
		/*Constructor de la clase.*/
		Trike(int id, int id_duenio, std::pair<int, int> centro);
};

#endif

