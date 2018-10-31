#ifndef SILO_H
#define SILO_H

#include "edificio.h"
#include <utility>

/*Clase que representa a un silo en el mundo de Dune.
Permiten guardar la especia recolectada ampliando la capacidad de las
refinerías.*/
class Silo: public Edificio{
	private:
		int capacidad;
	public:
		/*Constructor de la clase.*/
		Silo(int id, int id_duenio, std::pair<int, int> centro);

		/*Recibe una cantidad de especia y se la almacena en el silo. 
		Se devuelve 0 y entro toda la especia en la refineria. Se devuelve
		un numero mayor a 0 en caso contrario.*/
		int depositar_especia(int cantidad_especia);
};

#endif 