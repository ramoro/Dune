#ifndef REFINERIA_H
#define REFINERIA_H

#include "edificio.h"
#include <utility>

/*Clase que representa a una refineria en el mundo de Dune.
En ella las cosechadoras depositan la especia recolectada y
esta se transforma en dinero.*/
class Refineria: public Edificio{
	private:
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

		/*Recibe una cantidad de especia y se la almacena en la refineria. 
		Se devuelve 0 si entro toda la especia en la refineria. Se devuelve
		un numero mayor a 0 en caso contrario.*/
		/*int depositar_especia(int cantidad_especia);*/
};

#endif 
