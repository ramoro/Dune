#ifndef INFANTERIA_PESADA_H
#define INFANTERIA_PESADA_H

#include "unidad_infanteria.h"
#include <utility>
#include <vector>

/*Clase que representa una unidad de infanteria pesada en el mundo de Dune.
Unidad efectiva contra unidades blindadas, no así contra la infantería.*/
class InfanteriaPesada: public UnidadInfanteria {
	public:
		/*Constructor de la clase.*/
		InfanteriaPesada(int id, int id_duenio, std::pair<int, int> centro);

		/*Recibe el mapa y el id del objeto y devuelve todas las unidades
		afectadas por su ataque.*/
		virtual std::vector<int> atacar_objetivo(Mapa &mapa, int id_objetivo);
};

#endif
