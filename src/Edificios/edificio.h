#ifndef EDIFICIO_H
#define EDIFICIO_H

#include <utility>
#include "../objeto_dune.h"

/*Clase abstracta que representa a un edificio en el mundo de Dune.*/
class Edificio: public ObjetoDune {
	private:
		int gasto_energetico;
		std::pair<int, int> dimension;
		
	public:

		/*Constructor de la clase.*/
		Edificio(int costo_dinero, int gasto_energetico, 
		std::pair<int, int> dimension, int puntos_estructura, int id,
		int id_duenio, int base, int altura, std::pair<int, int> centro);
};

#endif
