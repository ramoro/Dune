#ifndef FABRICA_UNIDADES_MOVIBLES_H
#define FABRICA_UNIDADES_MOVIBLES_H

#include "unidad_movible.h"

/*Clase que representa a una fabrica o creador de unidades movibles
como vehiculos o unidades de ataque..*/
class FabricaUnidadesMovibles {
	public:
		/*Crea un objeto de la clase UnidadMovible segun el int recibido
		y devuelve el objeto por movimiento.*/
		UnidadMovible&& crear_unidad_movible(int id_tipo_unidad_movible);
};

#endif 