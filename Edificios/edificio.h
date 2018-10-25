#ifndef EDIFICIO_H
#define EDIFICIO_H

#include <utility>
#include "objeto_dune.h"

/*Clase abstracta que representa a un edificio en el mundo de Dune.*/
class Edificio: public ObjetoDune {
	private:
		int gasto_energetico;
		std::pair<int, int> dimension;
		int id;
		
	public:

		/*Constructor de la clase.*/
		Edificio(int costo_dinero, int gasto_energetico, 
		std::pair<int, int> dimension, int puntos_estructura);

		/*Devuelve el costo en dinero que conlleva construir el edificio.*/
		int obtener_costo();

		/*Recibe un int y se lo asigna al id.*/
		void asignar_id(int identificador_edificio);
};

#endif
