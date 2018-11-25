#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include <memory>
#include "../UnidadesMovibles/unidad_movible.h"
#include "estado.h"
#include "../mapa.h"

/*Clase que representa el estado de estar en movimiento
dentro del mapa.*/
class Movimiento: public Estado {
	public:
		/*Metodo virtual que actualiza el estado. En este caso
		se trata de mover a la unidad a la siguiente posicion del
		mejor camino que se le calculo segun el tiempo que paso y la
		velocidad que posee. Si esta ocupada la posicion
		a la que va a ir se vuelve a calcular el camino. Se mueve a la
		unidad y se quita la posicion del camino, actualizandosela a la
		unidad.*/
		virtual std::shared_ptr<Estado> actualizar(UnidadMovible *unidad,
		Mapa &mapa, int tiempo_transcurrido);
};

#endif 