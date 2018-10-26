#ifndef TERRENO_H
#define TERRENO_H

#include <string>

/*Clase abstracta que representa un terreno en el mundo de Dune.*/
class Terreno {
	private:
		std::string material;

	public:
		/*Constructor de la clase.*/
		Terreno(std::string material);

		/*Devuelve el nombre del material que posee el terreno.*/
		std::string obtener_nombre_material();	
};

#endif 