#ifndef OBJETO_DUNE_H
#define OBJETO_DUNE_H

#include <utility>
#include <vector>
#include "mensaje_protocolo.h"

class UnidadMovible;
class Cosechadora;

/*Clase abstracta que representa a un objeto del mundo dune que puede
ser tanto un edificio como una unidad movible (vehiculos y 
unidades de ataque).*/
class ObjetoDune {
	private:
		int vida;


	protected:
		int costo_dinero;
		int id;
		int id_tipo;
		int id_duenio;
		int base;
		int altura;
		std::pair<int, int> centro;
		std::vector<MensajeProtocolo> mensajes;
		bool fuera_de_juego;

	public:
		/*Constructor de la clase.*/
		ObjetoDune(int vida, int costo, int id, int id_duenio, int base, 
		int altura, std::pair<int, int> centro);

		/*Recibe el danio a disminuirle a la vida del objeto y devuelve
		la vida restante que le queda. En caso de devolver 0 o un numero
		negativo significa que la unidad murio/fallecio/se destruyo/caput.*/
		int reducir_vida(int danio);

		/*Devuelve el costo en dinero que conlleva obtener el objeto
		(puede ser el costo que trae construir un edificio o un vehiculo
		o el costo que trae entrenar a una unidad de ataque).*/
		int obtener_costo();

		/*Devuelve el id segun el tipo al que corresponde el objeto.
		Por ejemplo dentro de los edificios todas las Refinerias se 
		identifican con un id.*/
		int pedir_id_tipo();

		/*Devuelve el id unico del objeto.*/
		int pedir_id();

		/*Devuelve el id del jugador que posee el objeto.*/
		int pedir_id_duenio();

		/*Devuelve el ancho del objeto.*/
		int obtener_base();

		/*Devuelve la altura del objeto.*/
		int obtener_altura();

		/*Devuelve el la posicion del centro del objeto.*/
		std::pair<int, int> obtener_centro();

		/*Recibe un id de un jugador y le asigna como duenio
		al objeto el jugador pasado por parametro.*/
		void asignar_duenio(int id_nuevo_duenio);

		/*Recibe una coordenada nueva y se la asigna al centro.*/
		void set_centro(std::pair<int, int> centro_nuevo);

		/*Metodo virtual que dania a la unidad segun el danio provocado
		por la unidad atacante y el tiempo pasado.*/
		virtual int daniar(UnidadMovible* unidad_atacante, 
		int tiempo_trasncurrido);

		/*Metodo virtual que mata a la unidad (la setea en estado muerta).*/
		virtual void matar();

		/*Le da al mensaje la info. de la accion y los parametros
		adjuntos para mandarlo todo al cliente.*/
		void mensaje_muerte();

		/*Devuelve un vector con los mensajes listos para ser
		enviados al cliente.*/
		std::vector<MensajeProtocolo> obtener_mensajes_para_mandar();

		/*Vacia la lista de mensajes.*/
		void limpiar_lista_mensajes();

		/*Devuelve true si el objeto ya esta fuera de juego. False
		en caso contrario.*/
		bool esta_fuera_de_juego();

		/*Metodo virtual que en caso de tener especia
		le saca la especia al objeto dune segun cuanto extrae
		la cosechadora que recibe.*/
		virtual int remover_especia(Cosechadora *cosechadora);


		virtual int obtener_cantidad_especia();
};

#endif
