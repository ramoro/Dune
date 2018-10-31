#ifndef DEVASTADOR_H
#define DEVASTADOR_H

#include "unidad_movible.h"
#include <utility>

/*Clase que representa una unidad de un devastador en el mundo de Dune.
Es un tanque altamente blindado que al ser destruido explota daniando
todo aquel que este cerca.*/ 
class Devastador: public UnidadMovible {
	private:
		int danio_explosion;
		
	public:
		/*Constructor de la clase.*/
		Devastador(int id, int id_duenio, std::pair<int, int> centro);

		void armar();
};

#endif

