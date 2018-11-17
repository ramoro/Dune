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
		virtual std::vector<ObjetoDune*> atacar_objetivo(Mapa &mapa, 
		int id_objetivo);

		/*Mata a la unidad seteandola como muerta.*/
		virtual void matar();

		/*En caso de tener un ataque al morir lo ejecuta y devuelve
		un vector con los objetos afectados.*/
		virtual std::vector<ObjetoDune*> ataque_al_morir(Mapa &mapa);
};

#endif

