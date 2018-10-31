#ifndef INFANTERIA_PESADA_H
#define INFANTERIA_PESADA_H

#include "unidad_movible.h"
#include <utility>

/*Clase que representa una unidad de infanteria pesada en el mundo de Dune.
Unidad efectiva contra unidades blindadas, no así contra la infantería.*/
class InfanteriaPesada: public UnidadMovible {
	public:
		/*Constructor de la clase.*/
		InfanteriaPesada(int id, int id_duenio, std::pair<int, int> centro);
};

#endif
