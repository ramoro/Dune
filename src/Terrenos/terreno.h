#ifndef TERRENO_H
#define TERRENO_H

#include <string>

/*Clase abstracta que representa un terreno en el mundo de Dune.*/
class Terreno {
	private:
		int material;
		std::pair<int, int> centro;
		int base;
		int altura;

	public:
		/*Constructor de la clase.*/
		Terreno(int material);

		/*Devuelve el nombre del material que posee el terreno.*/
		int obtener_id_material();

		/*Metodo virtual que en caso de tener especia el terreno
		devuelve la cantidad que posee.*/
		virtual int obtener_cantidad_especia();

		/*Metodo virtual que en caso de tener especia el terreno
		se la reduce segun lo recibido por parametro y devuelve
		lo que queda.*/
		virtual int reducir_especia(int cantidad_a_reducir);
};

#endif 