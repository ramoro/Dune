#ifndef CANION_PLASMA_H
#define CANION_PLASMA_H

#include "arma.h"
#include "../src/config.h"

/*Clase que representa un canion de plasma en el mundo de Dune.*/
class CanionPlasma: public Arma {
	public:
		/*Constructor de la clase.*/
		CanionPlasma(Config &config);
};

#endif 