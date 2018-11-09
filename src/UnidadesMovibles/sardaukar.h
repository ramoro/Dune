#ifndef SARDAUKAR_H
#define SARDAUKAR_H

#include "unidad_infanteria.h"
#include <utility>
#include <vector>

/*Clase que representa una unidad de sardaukar en el mundo de Dune.
Es una unidad de elite concedida por el mismo Emperador.*/
class Sardaukar: public UnidadInfanteria {
	public:
		/*Constructor de la clase.*/
		Sardaukar(int id, int id_duenio, std::pair<int, int> centro, 
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