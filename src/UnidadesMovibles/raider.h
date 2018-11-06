#ifndef RAIDER_H
#define RAIDER_H

#include "vehiculo.h"
#include <utility>
#include <vector>

/*Clase que representa una unidad de un raider en el mundo de Dune.
Es un vehiculo similar a un Trike pero mucho mas rapido.*/
class Raider: public Vehiculo {
	public:
		/*Constructor de la clase.*/
		Raider(int id, int id_duenio, std::pair<int, int> centro);

		/*Recibe el mapa y el id del objeto y devuelve todas las unidades
		afectadas por su ataque.*/
		virtual std::vector<int> atacar_objetivo(Mapa &mapa, int id_objetivo);

		
		/*Recibe un mapa, mata a la unidad y la remueve del mapa. Devuelve
		un vector con el id de las unidades afectadas segun si la unidad
		afecto unidades vecinas al morir.*/
		virtual std::vector<int> matar(Mapa &mapa);
};

#endif

