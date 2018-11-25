#ifndef TERRENO_H
#define TERRENO_H

#include <string>
#include "../config.h"

/*Clase abstracta que representa un terreno en el mundo de Dune.*/
class Terreno {
	private:
		int cant_especia_actual;
		int material;
		std::pair<int, int> centro;
		int base;
		int altura;

	public:
		/*Constructor de la clase.*/
		Terreno(int material, Config &config);

		/*Devuelve el nombre del material que posee el terreno.*/
		int obtener_id_material();

		/*Recibe una cierta cantidad de especia a extraerle
		al terreno y se la saca. Devuelve la especia que le
		queda restante o un numero igual o menor a 0 en caso
		de no quedarle mas.*/
		int reducir_especia(int cantidad_a_reducir);

		/*Devuelve la cantidad de especia que tiene el terreno
		en el momento.*/
		int obtener_cantidad_especia();
};

#endif 