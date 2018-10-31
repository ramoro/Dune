#ifndef FABRICA_PESADA_H
#define FABRICA_PESADA_H

#include "edificio.h"
#include <string>
#include <utility>

/*Clase que representa a una fabrica pesada en el mundo de Dune.
Permite la construcción de vehículos blindados como los tanques.*/
class FabricaPesada: public Edificio{
	public:
		/*Constructor de la clase.*/
		FabricaPesada(int id, int id_duenio, std::pair<int, int> centro);

		/*Recibe un nombre del vehiculo a crear y lo crea, devolviendolo
		por movimiento.*/
		void crear_vehiculo_pesado(std::string nombre_vehiculo);
};

#endif 