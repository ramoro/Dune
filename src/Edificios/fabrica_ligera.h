#ifndef FABRICA_LIGERA_H
#define FABRICA_LIGERA_H

#include "edificio.h"
#include <string>

/*Clase que representa a una fabrica ligera en el mundo de Dune.
Permite la construccion de vehiculos ligeros como los Trike.*/
class FabricaLigera: public Edificio{
	public:
		/*Constructor de la clase.*/
		FabricaLigera();
};

#endif 