#ifndef TRAMPA_AIRE_H
#define TRAMPA_AIRE_H

#include "edificio.h"
#include <utility>

/*Clase que representa a una trampa de aire en el mundo de Dune.
Son turbinas eolicas que generan energia.*/
class TrampaAire: public Edificio{
	private:
		int intervalo_generacion_energia; //medido en segundos
		int energia_generada;
	public:
		/*Constructor de la clase.*/
		TrampaAire(int id, int id_duenio, std::pair<int, int> centro);
};

#endif 