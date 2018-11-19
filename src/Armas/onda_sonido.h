#ifndef ONDA_SONIDO_H
#define ONDA_SONIDO_H

#include "arma.h"

/*Clase que representa un arma de ondas de sonidos en el mundo de Dune.*/
class OndaSonido: public Arma {
	public:
		/*Constructor de la clase.*/
		OndaSonido(Config &config);
};

#endif 