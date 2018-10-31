#ifndef DESVIADOR_H
#define DESVIADOR_H

#include "unidad_movible.h"

/*Clase que representa una unidad de un desviador en el mundo de Dune.
Es un tanque que dispara un misil que al explotar esparce una nube tóxica y 
genera una confusion en la unidad impactada de manera que pasa a ser del
jugador.*/ 
class Desviador: public UnidadMovible {
	public:
		/*Constructor de la clase.*/
		Desviador(int id, int id_duenio, std::pair<int, int> centro);
};

#endif

