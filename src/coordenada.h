#ifndef COORDENADA_H
#define COORDENADA_H

#include "objeto_dune.h"
#include "Terrenos/terreno.h"
#include <string>
#include <memory>

class Cosechadora;

/*Clase que representa la coordenada de un mapa del mundo Dune.*/
class Coordenada {
	private:
		ObjetoDune* objeto;
		int estado;
		Terreno terreno;
		//int id;

	public:
		/*Constructor de la clase.*/
		Coordenada(int estado, Terreno terreno);

		/*Recibe un objeto del mundo Dune y ocupa la coordenada con
		ese objeto en caso de ser posible, devolviendo true. Si la coordenada
		esta ocupada no lo agrega y devuelve false.*/
		bool poner_objeto(ObjetoDune* objeto_dune);	

		/*Devuelve un string con el nombre del terreno que posee
		la coordenada.*/
		std::string obtener_terreno();

		/*Saca el objeto que tiene la coordenada (setea el puntero que tiene
		como atributo a NULL) y cambia su estado a VACIA.
		Precondicion: la coordenada esta ocupada con un objeto.*/
		void sacar_objeto();

		/*Devuelve true si la coordenada esta ocupada. False en caso contrario.*/
		bool esta_ocupada();

		/*Devuelve el id unico del objeto que contiene la coordenada.
		Precondicion: la coordenada posee un objeto situado en ella.*/
		int obtener_id_objeto_contenido();

		/*Marca como ocupada a la coordenada aunque no le pone ningun objeto.*/
		void marcar_como_ocupada();

		/*Marca como desocupada a una coordenada que no tiene un objeto
		pero que esta marcada como ocupada.
		Precondicion:la coordeanada esta marcada como ocupada.*/
		void marcar_como_desocupada();

};

#endif 