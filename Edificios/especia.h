#ifndef ESPECIA_H
#define ESPECIA_H

#include "terreno.h"
#include <string>

/*Clase que representa un terreno con especia en el mundo de Dune.*/
class Especia: public Terreno {
	private:
		int cant_especia_inicial;
		int cant_especia_actual;

	public:
		/*Constructor de la clase.*/
		Especia(std::string material);
		/*Recibe la cantidad de especia a reducir y se la saca
		al terreno.*/
		int sacar_especia(int cantidad);
};

#endif 