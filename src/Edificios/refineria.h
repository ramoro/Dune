#ifndef REFINERIA_H
#define REFINERIA_H

#include "edificio.h"

/*Clase que representa a una refineria en el mundo de Dune.
En ella las cosechadoras depositan la especia recolectada y
esta se transforma en dinero.*/
class Refineria: public Edificio{
	private:
		int capacidad;
	public:
		/*Constructor de la clase.*/
		Refineria();

		/*Recibe una cantidad de especia y se la almacena en la refineria. 
		Se devuelve 0 si entro toda la especia en la refineria. Se devuelve
		un numero mayor a 0 en caso contrario.*/
		int depositar_especia(int cantidad_especia);
};

#endif 