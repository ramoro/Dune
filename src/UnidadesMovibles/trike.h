#ifndef TRIKE_H
#define TRIKE_H

#include "vehiculo.h"
#include <utility>
#include <vector>

/*Clase que representa una unidad de un trike en el mundo de Dune.
Es un vehiculo rapido armado conametralladoras.*/
class Trike: public Vehiculo {
	public:
		/*Constructor de la clase.*/
		Trike(int id, int id_duenio, std::pair<int, int> centro);

		/*Recibe el mapa y el id del objeto y devuelve todas las unidades
		afectadas por su ataque.*/
		virtual std::vector<int> atacar_objetivo(Mapa &mapa, int id_objetivo);

		/*Recibe un mapa, mata a la unidad y la remueve del mapa. Devuelve
		un vector con pares (id_duenio, vida_restante).*/
		//virtual std::vector<std::pair<int, int>> matar(Mapa &mapa);
};

#endif

