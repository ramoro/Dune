#ifndef COORDENADA_H
#define COORDENADA_H

#include "objeto_dune.h"
#include "Terrenos/terreno.h"
#include <string>

/*Clase que representa la coordenada de un mapa del mundo Dune.*/
class Coordenada {
	private:
		ObjetoDune *objeto;
		int estado;
		Terreno terreno;

	public:
		/*Recibe un objeto del mundo Dune y ocupa la coordenada con
		ese objeto en caso de ser posible, devolviendo true. Si la coordenada
		esta ocupada no lo agrega y devuelve false.*/
		bool poner_objeto(ObjetoDune *objeto_dune);	

		/*Devuelve un string con el nombre del terreno que posee
		la coordenada.*/
		std::string obtener_terreno();

		/*Saca el objeto que tiene la coordenada (setea el puntero que tiene
		como atributo a NULL) y cambia su estado a VACIA.*/
		void sacar_objeto(); 

		Coordenada(int estado, Terreno terreno);
};

#endif 