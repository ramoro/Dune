#ifndef TANQUE_SONICO_H
#define TANQUE_SONICO_H

#include "unidad_movible.h"
#include <utility>

/*Clase que representa una unidad de un tanque sonico en el mundo de Dune.
Es un tanque que dispara ondas de sonidos que danian a todo aquel que se
encuentre en su paso, inclusive a unidades aliadas.*/
class TanqueSonico: public UnidadMovible {
	public:
		/*Constructor de la clase.*/
		TanqueSonico(int id, int id_duenio, std::pair<int, int> centro);
};

#endif

