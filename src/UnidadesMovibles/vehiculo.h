#ifndef VEHICULO_H
#define VEHICULO_H

#include "unidad_movible.h"
#include <memory>

/*Clase que representa vehiculo en el mundo de Dune.*/
class Vehiculo: public UnidadMovible {
	public:
		/*Constructor de la clase.*/
		Vehiculo(int rango, int velocidad, 
		float tiempo_creacion, int costo_dinero, int vida, 
		int id, int id_duenio, int base, int altura, std::pair<int, int> 
		centro);

		/*Recibe un puntero a una unidad movible que dania
		al objeto y el tiempo trasncurrido en el game loop. 
		Devuelve la vida restante que le queda
		al vehiculo luego de ser atacada.
		Si devuelve un 0 o menos significa que fue destruida.*/
		virtual int daniar(UnidadMovible* unidad_atacante,
		int tiempo_transcurrido);

		/*valida que el terreno no sea ni precipicio ni cima*/
		bool es_terreno_valido(int terreno);

		virtual int daniar_devastador(UnidadMovible* unidad_atacante);

};

#endif 