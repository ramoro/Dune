#ifndef PALACIO_H
#define PALACIO_H

#include "edificio.h"
#include <string>
#include <utility>

/*Clase que representa a un palacio en el mundo de Dune.
Habilita elentrenamiento, construcción y uso de unidades
más avanzadas.*/
class Palacio: public Edificio{
	public:
		/*Constructor de la clase.*/
		Palacio(int id, int id_duenio, std::pair<int, int> centro);
		
		/*Recibe un string con el nombre de la infanteria avanzada a crear
		y la crea. Devuelve la unidad por movimiento.*/
		void crear_infanteria_avanzada(std::string nombre_infanteria);
};

#endif 