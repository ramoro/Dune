#ifndef DEVASTADOR_H
#define DEVASTADOR_H

#include "vehiculo.h"
#include <utility>
#include <vector>

/*Clase que representa una unidad de un devastador en el mundo de Dune.
Es un tanque altamente blindado que al ser destruido explota daniando
todo aquel que este cerca.*/ 
class Devastador: public Vehiculo {
	private:
		int danio_explosion;
		
	public:
		/*Constructor de la clase.*/
		Devastador(int id, int id_duenio, std::pair<int, int> centro, 
			Root &root);

		/*Recibe el mapa y el id del objeto y devuelve todas las unidades
		afectadas por su ataque.*/
		virtual std::vector<int> atacar_objetivo(Mapa &mapa, int id_objetivo);

		/*Recibe un mapa, mata a la unidad y la remueve del mapa. Devuelve
		un vector con el id de unidades afectadas por la muerte
		del devastador.*/
		virtual std::vector<int> matar(Mapa &mapa);
};

#endif

