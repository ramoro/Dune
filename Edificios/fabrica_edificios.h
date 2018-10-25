#ifndef FABRICA_EDIFICIOS_H
#define FABRICA_EDIFICIOS_H

#include "edificio.h"

/*Clase que representa a una fabrica o creador de edificios.*/
class FabricaEdificios {
	public:
		/*Crea un objeto de la clase Edificio segun el int recibido
		y devuelve el objeto por movimiento.*/
		Edificio&& crear_edificio(int id_tipo_edificio);
};

#endif 