#ifndef COSECHADORA_H
#define COSECHADORA_H

#include "unidad_movible.h"

/*Clase que representa una unidad de una cosechadora en el mundo de Dune.
Es la unica unidad que puede recolectar la especia encontrada en las
arenas de Arrakis y llevarla a las refinerías.*/ 
class Cosechadora: public UnidadMovible {
	private:
		int especia_encima;
		
	public:
		/*Constructor de la clase.*/
		Cosechadora();
};

#endif

