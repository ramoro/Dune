#ifndef ATAQUE_H
#define ATAQUE_H

#include <memory>
#include "../UnidadesMovibles/unidad_movible.h"
#include "estado.h"
#include "../mapa.h"

/*Clase que representa el estado de ataque.*/
class Ataque: public Estado {
	private:
		std::shared_ptr<ObjetoDune> objeto_destino;
		std::pair<int, int> pos_a_atacar;

	public:
		/*Constructor de la clase.*/
		Ataque(std::shared_ptr<ObjetoDune> objetivo);

		/*Metodo virtual que actualiza el estado.*/
		virtual std::shared_ptr<Estado> actualizar(UnidadMovible *unidad,
		Mapa &mapa, double tiempo_transcurrido);
};

#endif 
