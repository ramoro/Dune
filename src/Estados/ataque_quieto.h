#ifndef ATAQUE_QUIETO_H
#define ATAQUE_QUIETO_H

#include <memory>
#include "../UnidadesMovibles/unidad_movible.h"
#include "estado.h"
#include "../mapa.h"

/*Clase que representa el estado de estar atacando en caso
de que haya una unidad enemiga cerca, pero no perisgue al
objetivo.*/
class AtaqueQuieto: public Estado {
	private:
		ObjetoDune* objetivo;
		
	public:
		/*Constructor de la clase.*/
		AtaqueQuieto(ObjetoDune* objetivo);

		/*Metodo virtual que actualiza el estado.*/
		virtual std::shared_ptr<Estado> actualizar(UnidadMovible *unidad,
		Mapa &mapa, int tiempo_transcurrido);
};

#endif 