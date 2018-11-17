#ifndef MOVIMIENTO_PARA_ATACAR_H
#define MOVIMIENTO_PARA_ATACAR_H

#include <memory>
#include "../UnidadesMovibles/unidad_movible.h"
#include "movimiento.h"
#include "../mapa.h"

/*Clase que representa el estado de estar en movimiento para ir a tacar.*/
class MovimientoParaAtacar: public Movimiento {
	private:
		std::shared_ptr<ObjetoDune> objeto_destino;
		std::pair<int, int> pos_destino;

	public:
		/*Constructor de la clase.*/
		MovimientoParaAtacar(std::shared_ptr<ObjetoDune> objetivo);

		/*Metodo virtual que actualiza el estado.*/
		virtual std::shared_ptr<Estado> actualizar(UnidadMovible *unidad,
		Mapa &mapa, double tiempo_transcurrido);
};

#endif 
