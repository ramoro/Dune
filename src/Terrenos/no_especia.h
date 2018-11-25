#ifndef NO_ESPECIA_H
#define NO_ESPECIA_H

#include "terreno.h"
#include <string>

/*Clase que representa un terreno sin especia en el mundo de Dune.*/
class NoEspecia: public Terreno {
	public:
		/*Constructor de la clase.*/
		NoEspecia(int material);
};

#endif 