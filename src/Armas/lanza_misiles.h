#ifndef LANZA_MISILES_H
#define LANZA_MISILES_H

#include "arma.h"
#include "../src/config.h"

/*Clase que representa un lanza misiles en el mundo de Dune.*/
class LanzaMisiles: public Arma {
	public:
		/*Constructor de la clase.*/
		LanzaMisiles(Config &config);
};

#endif 