#ifndef CANION_22MM_H
#define CANION_22MM_H

#include "arma.h"
#include "../src/config.h"

/*Clase que representa un canion 22mm en el mundo de Dune.*/
class Canion22mm: public Arma {
	public:
		/*Constructor de la clase.*/
		Canion22mm(Config &config);
};

#endif 