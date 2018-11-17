#ifndef CENTRO_CONSTRUCCION_H
#define CENTRO_CONSTRUCCION_H

#include "edificio.h"
#include <utility>

/*Clase que representa a un centro de construccion en el mundo de Dune.
Es el edificio principal de cada jugador, su destruccion implica la derrota
del mismo.*/
class CentroConstruccion: public Edificio{
	public:
		/*Constructor de la clase.*/
		CentroConstruccion(int id, int id_duenio, std::pair<int, int> centro,
		 Root &root);

		/*Devuelve true si el centro de construccion fue agregado al juego.
		False en caso contrario.*/
		virtual bool agregar_al_juego(Mapa &mapa, Jugador &jugador, int id_edificio, 
		int id_tipo_edificio);

		/*Se fija si el edifcio esta destruido y arma los mensajes
		correspondientes, ademas de realizar cosas extras segun el edificio.*/
		virtual void actualizar_existencia(Jugador &jugador);
};

#endif 