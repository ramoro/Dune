#ifndef COSECHADORA_H
#define COSECHADORA_H

#include "vehiculo.h"
#include <utility>

/*Clase que representa una unidad de una cosechadora en el mundo de Dune.
Es la unica unidad que puede recolectar la especia encontrada en las
arenas de Arrakis y llevarla a las refinerías.*/ 
class Cosechadora: public Vehiculo {
	private:
		int especia_encima;
		
	public:
		/*Constructor de la clase.*/
		Cosechadora(int id, int id_duenio, std::pair<int, int> centro,
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

