#ifndef MOVIMIENTO_PARA_DEPOSITAR_H
#define MOVIMIENTO_PARA_DEPOSITAR_H

#include <memory>
#include "../UnidadesMovibles/unidad_movible.h"
#include "movimiento.h"
#include "../mapa.h"

/*Clase que representa el estado de estar en movimiento 
para ir a depositar especia a una refineria.*/
class MovimientoParaDepositar: public Movimiento {
	private:
		Refineria* refineria_destino;
		std::shared_ptr<ObjetoDune> coordenada_a_volver;

	public:
		/*Constructor de la clase.*/
		MovimientoParaDepositar(Refineria* objetivo, 
		std::shared_ptr<ObjetoDune> terreno);

		/*Metodo virtual que actualiza el estado. Si la unidad llego
		a la refineria donde debe depositar la especia devuelve el estado
		Deposito.*/
		virtual std::shared_ptr<Estado> actualizar(UnidadMovible *unidad,
		Mapa &mapa, double tiempo_transcurrido);
};

#endif 
