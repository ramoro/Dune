#ifndef INFANTERIA_PESADA_H
#define INFANTERIA_PESADA_H

#include "unidad_movible.h"

/*Clase que representa una unidad de infanteria pesada en el mundo de Dune.
Unidad efectiva contra unidades blindadas, no así contra la infantería.*/
class InfanteriaPesada: public UnidadMovible {
	public:
		/*Constructor de la clase.*/
		InfanteriaPesada();
};

#endif
