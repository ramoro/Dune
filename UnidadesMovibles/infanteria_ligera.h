#ifndef INFANTERIA_LIGERA_H
#define INFANTERIA_LIGERA_H

#include "unidad_movible.h"

/*Clase que representa una unidad de infanteria ligera en el mundo de Dune.
Es una unidad basica que resulta fuerte cuando se la usa en grupo.*/
class InfanteriaLigera: public UnidadMovible {
	public:
		/*Constructor de la clase.*/
		InfanteriaLigera();
};

#endif
