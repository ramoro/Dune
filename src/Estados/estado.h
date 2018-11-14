#ifndef ESTADO_H
#define ESTADO_H

#include <memory>
#include "../UnidadesMovibles/unidad_movible.h"
#include "../mapa.h"

/*Clase que representa a un estado.*/
class Estado {
	public:
		/*Metodo virtual que acutaliza el estado.*/
		virtual std::shared_ptr<Estado> actualizar(UnidadMovible *unidad,
		Mapa &mapa) = 0;

		/*Devuelve un puntero al estado movimiento.*/
		std::shared_ptr<Estado> cambiar_a_movimiento();

};

#endif 