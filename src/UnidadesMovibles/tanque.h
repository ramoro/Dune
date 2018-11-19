#ifndef TANQUE_H
#define TANQUE_H

//#include "unidad_movible.h"
#include "vehiculo.h"
#include <utility>
#include <vector>

/*Clase que representa una unidad de un tanque comun en el mundo de Dune.
Es un vehiculo de ataque versatil. Unidad de combate por excelencia.*/ 
class Tanque: public Vehiculo {
	public:
		/*Constructor de la clase.*/
		Tanque(int id, int id_duenio, std::pair<int, int> centro, Config &config);

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

