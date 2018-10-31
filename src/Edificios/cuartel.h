#ifndef CUARTEL_H
#define CUARTEL_H

#include "edificio.h"
#include <string>
#include <utility>

/*Clase que representa a un cuartel en el mundo de Dune.
Es un centro de entrenamiento de las unidades de infantería.
Cada casa tiene un cuarte que la distingue.*/
class Cuartel: public Edificio{
	private:
		std::string casa;
	public:
		/*Constructor de la clase. Recibe un string con el nombre
		de la casa a la que pertenece.*/
		Cuartel(int id, int id_duenio, std::pair<int, int> centro);
		
		/*Recibe un string con el nombre de la infanteria a crear
		y la crea. Devuelve la unidad por movimiento.*/
		void crear_infanteria(std::string nombre_infanteria);
};

#endif 