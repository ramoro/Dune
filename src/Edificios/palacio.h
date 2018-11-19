#ifndef PALACIO_H
#define PALACIO_H

#include "edificio.h"
#include <string>
#include <utility>

/*Clase que representa a un palacio en el mundo de Dune.
Habilita elentrenamiento, construcción y uso de unidades
más avanzadas.*/
class Palacio: public Edificio{
	public:
		/*Constructor de la clase.*/
		Palacio(int id, int id_duenio, std::pair<int, int> centro, Config &config);
		
		/*Devuelve true si el palacio fue agregado al juego. False en caso
		contrario.*/
		virtual bool agregar_al_juego(Mapa &mapa, Jugador &jugador,
		 int id_edificio, int id_tipo_edificio);

		/*Se fija si el edifcio esta destruido y arma los mensajes
		correspondientes, ademas de realizar cosas extras segun el edificio.*/
		virtual void actualizar_existencia(Jugador &jugador);
};

#endif 