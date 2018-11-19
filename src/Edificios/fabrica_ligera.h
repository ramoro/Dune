#ifndef FABRICA_LIGERA_H
#define FABRICA_LIGERA_H

#include "edificio.h"
#include <string>
#include <utility>

/*Clase que representa a una fabrica ligera en el mundo de Dune.
Permite la construccion de vehiculos ligeros como los Trike.*/
class FabricaLigera: public Edificio{
	public:
		/*Constructor de la clase.*/
		FabricaLigera(int id, int id_duenio, std::pair<int, int> centro,
		 Config &config);

		/*Devuelve true si la fabrica ligera fue agregada al juego.
		False en caso contrario.*/
		virtual bool agregar_al_juego(Mapa &mapa, Jugador &jugador, int id_edificio, 
		int id_tipo_edificio);

		/*Se fija si el edifcio esta destruido y arma los mensajes
		correspondientes, ademas de realizar cosas extras segun el edificio.*/
		virtual void actualizar_existencia(Jugador &jugador);
};

#endif 