#ifndef SARDAUKAR_H
#define SARDAUKAR_H

#include "unidad_movible.h"
#include <utility>

/*Clase que representa una unidad de sardaukar en el mundo de Dune.
Es una unidad de elite concedida por el mismo Emperador.*/
class Sardaukar: public UnidadMovible {
	public:
		/*Constructor de la clase.*/
		Sardaukar(int id, int id_duenio, std::pair<int, int> centro);
};

#endif