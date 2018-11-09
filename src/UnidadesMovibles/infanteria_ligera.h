#ifndef INFANTERIA_LIGERA_H
#define INFANTERIA_LIGERA_H

#include "unidad_infanteria.h"
#include <utility>
#include <vector>

/*Clase que representa una unidad de infanteria ligera en el mundo de Dune.
Es una unidad basica que resulta fuerte cuando se la usa en grupo.*/
class InfanteriaLigera: public UnidadInfanteria {
	public:
		/*Constructor de la clase.*/
		InfanteriaLigera(int id, int id_duenio, std::pair<int, int> centro,
		 Root &root);

		/*Recibe el mapa y el id del objeto y devuelve todas las unidades
		afectadas por su ataque.*/
		virtual std::vector<int> atacar_objetivo(Mapa &mapa, int id_objetivo);

		/*Recibe un mapa, mata a la unidad y la remueve del mapa. Devuelve
		un vector con el id de las unidades afectadas segun si la unidad
		afecto unidades vecinas al morir.*/
		virtual std::vector<int> matar(Mapa &mapa);
};

#endif
