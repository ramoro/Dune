#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "arma.h"

/*Clase que representa una explosion en el mundo de Dune.*/
class Explosion: public Arma {
	private:
		int dimesion_altura;
		int dimesion_base;
	public:
		/*Constructor de la clase.*/
		Explosion();

		/*Devuelve la dimension en altura de la explosion.*/
		int pedir_dimension_altura();
		
		/*Devuelve la dimension en base de la explosion.*/
		int pedir_dimension_base();
};
#endif 