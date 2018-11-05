#ifndef FREMEN_H
#define FREMEN_H

#include "unidad_infanteria.h"
#include <utility>
#include <vector>

/*Clase que representa una unidad de fremen en el mundo de Dune.
Guerrero nativo del planeta Arrakis que sabe como moverse en el
desierto.*/
class Fremen: public UnidadInfanteria {
	public:
		/*Constructor de la clase.*/
		Fremen(int id, int id_duenio, std::pair<int, int> centro);

		/*Recibe el mapa y el id del objeto y devuelve todas las unidades
		afectadas por su ataque.*/
		virtual std::vector<int> atacar_objetivo(Mapa &mapa, int id_objetivo);

		/*Recibe un mapa, mata a la unidad y la remueve del mapa. Devuelve
		un vector con pares (id_duenio, vida_restante) segun si la unidad
		afecto unidades vecinas al morir.*/
		virtual std::vector<std::pair<int, int>> matar(Mapa &mapa);

};

#endif
