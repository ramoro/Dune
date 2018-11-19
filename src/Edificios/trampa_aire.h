#ifndef TRAMPA_AIRE_H
#define TRAMPA_AIRE_H

#include "edificio.h"
#include <utility>

/*Clase que representa a una trampa de aire en el mundo de Dune.
Son turbinas eolicas que generan energia.*/
class TrampaAire: public Edificio{
	private:
		int intervalo_generacion_energia; //medido en segundos
	public:
		/*Constructor de la clase.*/
		TrampaAire(int id, int id_duenio, std::pair<int, int> centro,
		 Config &config);

		/*Devuelve true si se pudo agregar la trampa de aire al juego.
		False en caso contrario.*/
		virtual bool agregar_al_juego(Mapa &mapa, Jugador &jugador, int id_edificio, 
		int id_tipo_edificio);

		/*Se fija si el edifcio esta destruido y arma los mensajes
		correspondientes, ademas de realizar cosas extras segun el edificio.*/
		virtual void actualizar_existencia(Jugador &jugador);
};

#endif 