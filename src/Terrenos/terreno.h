#ifndef TERRENO_H
#define TERRENO_H

#include <string>

/*Clase abstracta que representa un terreno en el mundo de Dune.*/
class Terreno {
	private:
		std::string material;
		std::pair<int, int> centro;
		int base;
		int altura;

	public:
		/*Constructor de la clase.*/
		Terreno(std::string material);

		/*Devuelve el nombre del material que posee el terreno.*/
		std::string obtener_nombre_material();	
};

#endif 