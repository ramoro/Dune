#ifndef CUARTEL_H
#define CUARTEL_H

#include "edificio.h"
#include <string>
#include <utility>

/*Clase que representa a un cuartel en el mundo de Dune.
Es un centro de entrenamiento de las unidades de infantería.
Cada casa tiene un cuarte que la distingue.*/
class Cuartel: public Edificio{
	private:
		std::string casa;
	public:
		/*Constructor de la clase. Recibe un string con el nombre
		de la casa a la que pertenece.*/
		Cuartel(int id, int id_duenio, std::pair<int, int> centro, Root &root);
		
		/*Devuelve true si el cuartel fue agregado al juego.
		False en caso contrario.*/
		virtual bool agregar_al_juego(Mapa &mapa, Jugador &jugador, int id_edificio, 
		int id_tipo_edificio);

		/*Recibe el mapa y el jugador que posee el edificio y se lo
		elimina de ambos a este.*/
		virtual void destruir(Mapa &mapa, Jugador &jugador);
};

#endif 