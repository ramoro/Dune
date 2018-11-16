#ifndef MUERTE_H
#define MUERTE_H

#include <memory>
#include "../UnidadesMovibles/unidad_movible.h"
#include "estado.h"
#include "../mapa.h"

/*Clase que representa el estado de estar muerto.*/
class Muerte: public Estado {
	public:
		/*Metodo virtual que actualiza el estado.*/
		virtual std::shared_ptr<Estado> actualizar(UnidadMovible *unidad,
		Mapa &mapa, double tiempo_transcurrido);
};

#endif 