#ifndef REFINERIA_H
#define REFINERIA_H

#include "edificio.h"
#include <utility>

/*Clase que representa a una refineria en el mundo de Dune.
En ella las cosechadoras depositan la especia recolectada y
esta se transforma en dinero.*/
class Refineria: public Edificio{
	private:
		int cantidad_especia;
		int capacidad;
	public:
		/*Constructor de la clase.*/
		Refineria(int id, int id_duenio, std::pair<int, int> centro,
		 Config &config);

		/*Devuelve true si se pudo agregar la refineria al juego. False
		en caso contrario.*/
		virtual bool agregar_al_juego(Mapa &mapa, Jugador &jugador, int id_edificio, 
		int id_tipo_edificio);

		/*Se fija si el edifcio esta destruido y arma los mensajes
		correspondientes, ademas de realizar cosas extras segun el edificio.*/
		virtual void actualizar_existencia(Jugador &jugador);

		/*Recibe una cantidad de especia y se la agrega a la refineria.*/
		void agregar_especia(int especia);

		/*Recibe una cantidad de especia y se la reduce a la que tiene
		la refineria.*/
		void reducir_especia(int especia);

		/*Devuelve la cantidad de especia que tiene almacenada
		la refineria.*/
		int obtener_especia();
};

#endif 
