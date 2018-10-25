#ifndef CENTRO_CONSTRUCCION_H
#define CENTRO_CONSTRUCCION_H

#include "edificio.h"

/*Clase que representa a un centro de construccion en el mundo de Dune.
Es el edificio principal de cada jugador, su destruccion implica la derrota
del mismo.*/
class CentroConstruccion: public Edificio{
	public:
		/*Constructor de la clase.*/
		CentroConstruccion();
};

#endif 