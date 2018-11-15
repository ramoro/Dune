#ifndef ESTADO_H
#define ESTADO_H

#include <memory>
#include "../UnidadesMovibles/unidad_movible.h"
#include "../mapa.h"

/*Clase que representa a un estado.*/
class Estado {
	public:
		/*Metodo virtual que recibe un puntero a una unidad movible, al mapa y
		el tiempo transcurrido y actualiza su estado dentro del mismo.*/
		virtual std::shared_ptr<Estado> actualizar(UnidadMovible *unidad,
		Mapa &mapa, double tiempo_transcurrido) = 0;

		/*Devuelve un puntero al estado movimiento.*/
		std::shared_ptr<Estado> cambiar_a_movimiento();

};

#endif 