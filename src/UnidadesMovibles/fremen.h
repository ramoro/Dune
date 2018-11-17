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
		Fremen(int id, int id_duenio, std::pair<int, int> centro, Root &root);

		/*Recibe el mapa y el id del objeto y devuelve todas las unidades
		afectadas por su ataque.*/
		virtual std::vector<ObjetoDune*> atacar_objetivo(Mapa &mapa, 
		int id_objetivo);

		/*Mata a la unidad seteandola como muerta.*/
		virtual void matar();

		/*En caso de tener un ataque al morir lo ejecuta y devuelve
		un vector con los objetos afectados.*/
		virtual std::vector<ObjetoDune*> ataque_al_morir(Mapa &mapa);

};

#endif
