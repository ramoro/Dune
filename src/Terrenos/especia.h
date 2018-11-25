#ifndef ESPECIA_H
#define ESPECIA_H

#include "terreno.h"
#include "../config.h"
#include <string>

/*Clase que representa un terreno con especia en el mundo de Dune.*/
class Especia: public Terreno {
	private:
		//int cant_especia_inicial;
		int cant_especia_actual;

	public:
		/*Constructor de la clase.*/
		Especia(std::string material, Config &config);

		/*Recibe la cantidad de especia a reducir y se la saca
		al terreno.*/
		int sacar_especia(int cantidad);

		/*Devuelve la cantidad de especia que tiene el terreno
		en el momento.*/
		virtual int obtener_cantidad_especia();

		/*Recibe una cierta cantidad de especia a extraerle
		al terreno y se la saca. Devuelve la especia que le
		queda restante o un numero igual o menor a 0 en caso
		de no quedarle mas.*/
		virtual int reducir_especia(int cant_a_reducir);
};

#endif 