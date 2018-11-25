#ifndef CANION_H
#define CANION_H

#include "arma.h"
#include "../src/config.h"

/*Clase que representa un canion en el mundo de Dune.*/
class Canion: public Arma {
	public:
		/*Constructor de la clase.*/
		Canion(Config &config);
};

#endif 