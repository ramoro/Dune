#ifndef EDIFICIO_H
#define EDIFICIO_H

#include <utility>
#include <memory>
#include <vector>
#include <list>
#include <map>
#include "../objeto_dune.h"
#include "../jugador.h"
#include "../mapa.h"
#include "../UnidadesMovibles/unidad_movible.h"
#include "../UnidadesMovibles/fabrica_unidades_movibles.h"

/*Clase abstracta que representa a un edificio en el mundo de Dune.*/
class Edificio: public ObjetoDune {
	private:
		int aporte_energetico;
		std::pair<int, int> dimension;
		float porcentaje_recuperacion;
		FabricaUnidadesMovibles fabrica_unidades_movibles;
		std::map<int, std::shared_ptr<UnidadMovible>> unidades_entrenando;
	
	protected:
		int estado;	
	
	public:

		/*Constructor de la clase.*/
		Edificio(int aporte_energetico, int costo_dinero, 
		int puntos_estructura, int id,
		int id_duenio, int base, int altura, std::pair<int, int> centro);

		/*Devuelve el aporte energetico del edificio, que puede ser tanto
		positivo o como negativo (resta energia).*/
		int obtener_aporte_energetico();
		
		virtual int daniar_devastador(UnidadMovible* unidad_atacante);

		/*Recibe el mapa del juego, el jugador al que corresponde el edificio,
		su id y su id de tipo y lo agrega al juego (al mapa
		y al jugador).*/
		bool agregar(Mapa &mapa, Jugador &jugador, int id_edificio, 
		int id_tipo_edificio);

		/*Metodo virtual puro que agrega el edificio al juego.*/
		virtual bool agregar_al_juego(Mapa &mapa, Jugador &jugador, 
		int id_edificio, int id_tipo_edificio) = 0;

		/*Recibe un puntero a una unidad movible que dania
		al objeto y el tiempo transcurrido en el game loop. 
		Devuelve la vida restante que le queda
		al edificio luego de ser atacada.
		Si devuelve un 0 o menos significa que fue destruida.*/
		virtual int daniar(UnidadMovible* unidad_atacante, 
		int tiempo_transcurrido);

		/*Recibe el jugador duenio del edificio
		y crea una unidad segun el id del tipo y asignandole la id_unidad
		tambien pasados por parametro y la agrega tanto al jugador como 
		al mapa. Los valores de los atributos de la unidad creada
		estaran determinados por el parseo de Config. Devuelve true si
		se pudo agregar la unidad. False en caso contrario.*/
		bool se_puede_agregar_unidad(Jugador &jugador, int id_tipo_unidad,
		int id_unidad, Config &config);

		/*Recibe el jugador y le aumenta un porcentaje en dinero
		de lo que le costo el edificio, el cual se mata.*/
		void vender(Jugador &jugador);

		/*Recibe el puntero a un objeto que se agrego recientemente
		al juego y se agrega la accion y los parametros adjuntos a la misma
		segun el protocolo a la clase MensajeProtocolo del objeto.*/
		void serializar_mensaje_creacion_objeto(std::shared_ptr<ObjetoDune> 
		unidad);

		/*Recibe el mapa del juego y el id del tipo de la unidad que se
		estaba entrenando y se quier agregar y se la agrega al mapa. Devuelve
		el puntero a la nueva unidad creada.*/
		std::shared_ptr<UnidadMovible> agregar_unidad(Mapa &mapa, 
		int id_tipo_unidad); 

		/*Recibe un un id de tipo de una unidad y un tiempo para reducir el 
		tiempo de entrenamiento
		faltante en caso de que se este entrenando a alguna unidad. Devuelve
		false si no se esta entrenando una unidad o si no se termino
		de entrenar la que se pidio que se entrene. True en caso contrario.*/
		bool avanzar_tiempo_creacion(int tiempo_transcurrido, 
		int id_tipo_unidad);

		/*Setea el estado del edificio en destruido.*/
		virtual void matar();

		/*Metodo virtual puro que actualiza al edificio segun si 
		ha sido destruido o no.*/
		virtual void actualizar_existencia(Jugador &jugador) = 0;

		/*Devuelve el la posicion del centro del objeto.*/
		virtual	std::pair<int, int> obtener_esquina();

		/*Se agrega dentro de la clase ObjetoDune la accion 
		muerte del edificio dentro del juego y los parametros adjuntos a la 
		misma segun el protocolo a la clase MensajeProtocolo del edificio.*/
		void serializar_mensaje_muerte();

		/*Se agrega el evento de que perdio el jugador duenio del edificio
		destruido y los parametros adjuntos al evento segun el protocolo a 
		la clase MensajeProtocolo del edificio.*/
		void serializar_mensaje_perdio_jugador();

		/*Devuelve la distancia euclideana dado un centro para con el
		centro del propio edificio*/
		int calcular_distancia_baldosas(std::pair<int,int> &centro_otro);
};

#endif
