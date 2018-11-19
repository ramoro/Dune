#ifndef FABRICA_UNIDADES_MOVIBLES_H
#define FABRICA_UNIDADES_MOVIBLES_H

#include "unidad_movible.h"
#include <utility>
#include <memory>

/*Clase que representa a una fabrica o creador de unidades movibles
como vehiculos o unidades de ataque.*/
class FabricaUnidadesMovibles {
	public:
		/*Crea un objeto de la clase UnidadMovible segun el int recibido
		y devuelve el objeto por movimiento.*/
		std::shared_ptr<UnidadMovible> crear_unidad_movible(
		int id_tipo_unidad_movible, int id, int id_duenio, 
		std::pair<int, int> centro, Config &config);
};

#endif 