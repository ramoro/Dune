#ifndef DEPOSTIO_H
#define DEPOSITO_H

#include <memory>
#include "../mapa.h"
#include "../UnidadesMovibles/unidad_movible.h"
#include "estado.h"

/*Clase que representa el estado de estar depositando
especia en una refineria.*/
class Deposito: public Estado {
	private:
		Refineria* refineria_deposito;
		int contador_segundo; //lo cuenta en milisegundos. Al llegar 
								 //al segundo se reinicia.
		int tiempo_transcurrido;
		std::shared_ptr<ObjetoDune> especia_a_volver;

	public:
		/*Constructor de la clase.*/
		Deposito(Refineria* objetivo, std::shared_ptr<ObjetoDune> coord);

		/*Metodo virtual que actualiza el estado. Si la unidad llego
		a la refineria donde debe depositar la especia devuelve el estado
		Deposito.*/
		virtual std::shared_ptr<Estado> actualizar(UnidadMovible *unidad,
		Mapa &mapa, int tiempo_transcurrido);
};

#endif 
