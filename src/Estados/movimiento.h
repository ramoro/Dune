#ifndef MOVIMIENTO_H
#define MOVIMIENTO_H

#include <memory>
#include "../UnidadesMovibles/unidad_movible.h"
#include "estado.h"

/*Clase que representa a un estado.*/
class Movimiento: public Estado {
	public:
		/*Metodo virtual que acutaliza el estado.*/
		virtual std::shared_ptr<Estado> actualizar(UnidadMovible *unidad);
};

#endif 