#ifndef BALDOSA_H
#define BALDOSA_H

#include "objeto_dune.h"
#include "Terrenos/terreno.h"
#include <string>
#include <memory>


/*Clase que representa una baldosa de un mapa del mundo Dune.*/
class Baldosa: public ObjetoDune {
	private:
		ObjetoDune* objeto;
		int estado;
		Terreno terreno;
		int id;
		std::pair<int,int> esquina;
		MensajeProtocolo mensaje;

	public:
		/*Constructor de la clase.*/
		Baldosa(int estado, Terreno terreno, int id, 
		std::pair<int, int> posicion);

		/*Recibe un objeto del mundo Dune y ocupa la baldosa con
		ese objeto en caso de ser posible, devolviendo true. Si la baldosa
		esta ocupada no lo agrega y devuelve false.*/
		bool poner_objeto(ObjetoDune* objeto_dune);	

		/*Devuelve un string con el nombre del terreno que posee
		la baldosa.*/
		int obtener_terreno();

		/*Saca el objeto que tiene la baldosa (setea el puntero que tiene
		como atributo a NULL) y cambia su estado a VACIA.
		Precondicion: la baldosa esta ocupada con un objeto.*/
		void sacar_objeto();

		/*Devuelve true si la baldosa esta ocupada. False en caso contrario.*/
		bool esta_ocupada();

		/*Devuelve el id unico del objeto que contiene la baldosa.
		Precondicion: la baldosa posee un objeto situado en ella.*/
		int obtener_id_objeto_contenido();

		/*Marca como ocupada a la baldosa aunque no le pone ningun objeto.*/
		void marcar_como_ocupada();

		/*Marca como desocupada a una baldosa que no tiene un objeto
		pero que esta marcada como ocupada.
		Precondicion:la coordeanada esta marcada como ocupada.*/
		void marcar_como_desocupada();

		void serializar_mensaje_salida();

		/*Se saca al terreno de la baldosa especia si es que tiene
		segun la cantidad que puede sacar la unidad recibida. Devuelve
		la cantidad que le queda de especia al terreno de la baldosa.*/
		virtual int remover_especia(Cosechadora* unidad_atacante);

		/*Avisa que la baldosa en caso de tener especia ya no tiene
		mas y se avisa armando un mensaje para enviar al cliente.*/
		virtual void matar();
};

#endif 