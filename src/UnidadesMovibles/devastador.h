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
		std::vector<int> config_explosion;

	public:
		/*Constructor de la clase.*/
		Devastador(int id, int id_duenio, std::pair<int, int> centro, 
			Root &root);

		/*Recibe el mapa y el id del objeto y devuelve todas las unidades
		afectadas por su ataque.*/
		virtual std::vector<ObjetoDune*> atacar_objetivo(Mapa &mapa, 
		int id_objetivo);

		/*Mata a la unidad seteandola como muerta. Le equipa el arma
		de explosion para daniar con su explosion al morir.*/
		virtual void matar();

		/*En caso de tener un ataque al morir lo ejecuta y devuelve
		un vector con los objetos afectados.*/
		virtual std::vector<ObjetoDune*> ataque_al_morir(Mapa &mapa);
};

#endif

