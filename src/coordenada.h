#ifndef COORDENADA_H
#define COORDENADA_H

#include "objeto_dune.h"
#include "Terrenos/terreno.h"
#include <string>
#include <memory>

/*Clase que representa la coordenada de un mapa del mundo Dune.*/
class Coordenada {
	private:
		std::shared_ptr<ObjetoDune> objeto;
		int estado;
		Terreno terreno;

	public:
		/*Recibe un objeto del mundo Dune y ocupa la coordenada con
		ese objeto en caso de ser posible, devolviendo true. Si la coordenada
		esta ocupada no lo agrega y devuelve false.*/
		bool poner_objeto(std::shared_ptr<ObjetoDune> objeto_dune);	

		/*Devuelve un string con el nombre del terreno que posee
		la coordenada.*/
		std::string obtener_terreno();

		/*Saca el objeto que tiene la coordenada (setea el puntero que tiene
		como atributo a NULL) y cambia su estado a VACIA.*/
		void sacar_objeto();

		/*Devuelve true si la coordenada esta ocupada. False en caso contrario.*/
		bool esta_ocupada();

		/*Devuelve el id unico del objeto que contiene la coordenada.
		Precondicion: la coordenada posee un objeto situado en ella.*/
		int obtener_id_objeto_contenido();

		Coordenada(int estado, Terreno terreno);
};

#endif 