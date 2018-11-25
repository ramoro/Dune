#ifndef RIFLE_ASALTO_H
#define RIFLE_ASALTO_H

#include "arma.h"
#include "../src/config.h"

/*Clase que representa un rifle de asalto en el mundo de Dune.*/
class RifleAsalto: public Arma {
	public:
		/*Constructor de la clase.*/
		RifleAsalto(Config &config);
};

#endif 