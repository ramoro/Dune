#ifndef FABRICA_EDIFICIOS_H
#define FABRICA_EDIFICIOS_H

#include "edificio.h"
#include <utility>
#include <memory>

/*Clase que representa a una fabrica o creador de edificios.*/
class FabricaEdificios {
	public:
		/*Crea un objeto de la clase Edificio segun el int recibido
		y devuelve un puntero al objeto*/
		std::shared_ptr<Edificio> crear_edificio(int id_tipo_edificio, int id,
		int id_duenio, std::pair<int, int> centro,Root &root);
};

#endif 