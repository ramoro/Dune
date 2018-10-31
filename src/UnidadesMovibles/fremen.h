#ifndef FREMEN_H
#define FREMEN_H

#include "unidad_movible.h"
#include <utility>

/*Clase que representa una unidad de fremen en el mundo de Dune.
Guerrero nativo del planeta Arrakis que sabe como moverse en el
desierto.*/
class Fremen: public UnidadMovible {
	public:
		/*Constructor de la clase.*/
		Fremen(int id, int id_duenio, std::pair<int, int> centro);

};

#endif
