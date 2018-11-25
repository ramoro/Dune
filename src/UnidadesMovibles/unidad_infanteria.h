#ifndef UNIDAD_INFANTERIA_H
#define UNIDAD_INFANTERIA_H

#include "unidad_movible.h"
#include <memory>

/*Clase abstracta que representa unidad de infanteria en el mundo de Dune.*/
class UnidadInfanteria: public UnidadMovible {
	public:
		/*Constructor de la clase.*/
		UnidadInfanteria(int rango, int velocidad, 
		double tiempo_creacion, int costo_dinero, int vida, 
		int id, int id_duenio, int base, int altura, std::pair<int, int> 
		centro);
		
		/*Recibe un puntero a una unidad movible que dania
		al objeto. Devuelve la vida restante que le queda
		a la undad de infenteria luego de ser atacada.
		Si devuelve un 0 o menos significa que fue destruida.*/
		virtual int daniar(UnidadMovible* unidad_atacante);

		/*valida que el terreno no sea precipicio*/
		bool es_terreno_valido(int terreno);
};

#endif 