#ifndef DESVIADOR_H
#define DESVIADOR_H

#include "vehiculo.h"
#include <vector>

/*Clase que representa una unidad de un desviador en el mundo de Dune.
Es un tanque que dispara un misil que al explotar esparce una nube tóxica y 
genera una confusion en la unidad impactada de manera que pasa a ser del
jugador.*/ 
class Desviador: public Vehiculo {
	public:
		/*Constructor de la clase.*/
		Desviador(int id, int id_duenio, std::pair<int, int> centro,
		 Config &config);

		/*Recibe el mapa y el id del objeto y devuelve todas las unidades
		afectadas por su ataque.*/
		virtual std::vector<ObjetoDune*> atacar_objetivo(Mapa &mapa, 
		int id_objetivo);

		/*Mata a la unidad seteandola como muerta.*/
		virtual void matar();

		/*En caso de tener un ataque al morir lo ejecuta y devuelve
		un vector con los objetos afectados.*/
		virtual std::vector<ObjetoDune*> ataque_al_morir(Mapa &mapa);

		/*Recibe el id de la unidad a cambiar de equipo ademas del
		id del tipo al que pertenece  y crea un mensaje 
		asigandole la accion de cambio de jugador junto con sus parametros 
		segun indica el protocolo.*/
		void serializar_mensaje_cambio_equipo(int id_objetivo,
		int id_tipo_objetivo);
};

#endif
