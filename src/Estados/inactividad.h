#ifndef INACTIVIDAD_H
#define INACTIVIDAD_H

#include <memory>
#include "../UnidadesMovibles/unidad_movible.h"
#include "estado.h"
#include "../mapa.h"

/*Clase que representa el estado de estar parado inactivo.*/
class Inactividad: public Estado {
	public:
		/*Metodo virtual que actualiza el estado.*/
		virtual std::shared_ptr<Estado> actualizar(UnidadMovible *unidad,
		Mapa &mapa, int tiempo_transcurrido);
};

#endif 