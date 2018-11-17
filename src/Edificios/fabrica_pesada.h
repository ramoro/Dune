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
		FabricaPesada(int id, int id_duenio, std::pair<int, int> centro,
		 Root &root);

		/*Devuelve true si la fabrica pesada fue agregada al juego.
		False en caso contrario.*/
		virtual bool agregar_al_juego(Mapa &mapa, Jugador &jugador, int id_edificio, 
		int id_tipo_edificio);

		/*Se fija si el edifcio esta destruido y arma los mensajes
		correspondientes, ademas de realizar cosas extras segun el edificio.*/
		virtual void actualizar_existencia(Jugador &jugador);
};

#endif 