#ifndef TANQUE_SONICO_H
#define TANQUE_SONICO_H

//#include "unidad_movible.h"
#include "vehiculo.h"
#include <utility>
#include <vector>

/*Clase que representa una unidad de un tanque sonico en el mundo de Dune.
Es un tanque que dispara ondas de sonidos que danian a todo aquel que se
encuentre en su paso, inclusive a unidades aliadas.*/
class TanqueSonico: public Vehiculo {
	private:
	//	int expansion_altura_arma_sonica; //la idea es que sean mayores que
	//	int expansion_base_arma_sonica; //las dimensiones del tanque
	
	public:
		/*Constructor de la clase.*/
		TanqueSonico(int id, int id_duenio, std::pair<int, int> centro,
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
};

#endif

