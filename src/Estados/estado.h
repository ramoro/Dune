#ifndef ESTADO_H
#define ESTADO_H

#include <memory>
#include "../UnidadesMovibles/unidad_movible.h"
#include "../mapa.h"
#include "../Edificios/refineria.h"
#include <string>

/*Clase que representa a un estado.*/
class Estado {
	protected:
		std::string nombre;
	public:
		/*Metodo virtual que recibe un puntero a una unidad movible, al mapa y
		el tiempo transcurrido y actualiza su estado dentro del mismo.*/
		virtual std::shared_ptr<Estado> actualizar(UnidadMovible *unidad,
		Mapa &mapa, int tiempo_transcurrido) = 0;

		/*Devuelve un puntero al estado movimiento.*/
		std::shared_ptr<Estado> cambiar_a_movimiento();

		/*Recibe un puntero a un objeto para ir a atacar y 
		devuelve un puntero al estado movimiento para atacar.*/
		std::shared_ptr<Estado> cambiar_a_movimiento_para_atacar(
		std::shared_ptr<ObjetoDune> objetivo);

		/*Recibe un puntero a un objeto para atacar y 
		devuelve un puntero al estado ataque.*/
		std::shared_ptr<Estado> cambiar_a_ataque(
		std::shared_ptr<ObjetoDune> objetivo);

		/*Devuelve un puntero al estado muerte.*/
		std::shared_ptr<Estado> cambiar_a_muerte();

		/*Devuelve un puntero al estado inactividad*/
		std::shared_ptr<Estado> cambiar_a_inactividad();

		/*Recibe un puntero al objeto donde va a ir a depositar la especia
		y el terreno a donde volvera a extraer mas especia
		y devuelve un puntero al estado movimiento para depositar.*/
		std::shared_ptr<Estado> cambiar_a_movimiento_para_depositar(
		Refineria* objetivo, std::shared_ptr<ObjetoDune> terreno);

		std::string pedir_nombre();

};

#endif 