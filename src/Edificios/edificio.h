#ifndef EDIFICIO_H
#define EDIFICIO_H

#include <utility>
#include <memory>
#include <vector>
#include <list>
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
		int porcentaje_recuperacion;
		FabricaUnidadesMovibles fabrica_unidades_movibles;
		int estado;
		std::list<std::shared_ptr<UnidadMovible>> unidades_entrenando;
		
	public:

		/*Constructor de la clase.*/
		Edificio(int aporte_energetico, int costo_dinero, 
		int puntos_estructura, int id,
		int id_duenio, int base, int altura, std::pair<int, int> centro);

		/*Devuelve el aporte energetico del edificio, que puede ser tanto
		positivo o como negativo (resta energia).*/
		int obtener_aporte_energetico();

		/*Recibe el mapa del juego, el jugador al que corresponde el edificio,
		su id y su id de tipo y lo agrega al juego (al mapa
		y al jugador).*/
		bool agregar(Mapa &mapa, Jugador &jugador, int id_edificio, 
		int id_tipo_edificio);

		/*Metodo virtual puro que agrega el edificio al juego.*/
		virtual bool agregar_al_juego(Mapa &mapa, Jugador &jugador, 
		int id_edificio, int id_tipo_edificio) = 0;

		/*Recibe un puntero a una unidad movible que dania
		al objeto. Devuelve la vida restante que le queda
		al edificio luego de ser atacada.
		Si devuelve un 0 o menos significa que fue destruida.*/
		int daniar(std::shared_ptr<UnidadMovible> unidad_atacante);

		/*Metodo virtual puro que saca al edificio del juego.*/
		virtual void destruir(Mapa &mapa, Jugador &jugador) = 0;

		/*Recibe el mapa y el jugador al que pertenece el edificio
		y lo remueve de ambos.*/
		void eliminar(Mapa &mapa, Jugador &jugador); //VER LO DEL BOOLEANO PARA INDICAR FIN JUEGO

		/*Recibe el mapa y el jugador al que pertenece el edificio y
		lo demuele, devolviendo la fraccion de plata que se recupera del
		mismo.*/
		void autodemoler(Mapa &mapa, Jugador &jugador);

		/*Recibe el jugador duenio del edificio
		y crea una unidad segun el id del tipo y asignandole la id_unidad
		tambien pasados por parametro y la agrega tanto al jugador como 
		al mapa. Los valores de los atributos de la unidad creada
		estaran determinados por el parseo de Root. Devuelve true si
		se pudo agregar la unidad. False en caso contrario.*/
		bool se_puede_agregar_unidad(Jugador &jugador, int id_tipo_unidad,
		int id_unidad, Root &root);

		/*Recibe el puntero a un objeto que se agrego recientemente
		al juego y se agrega la accion y los parametros adjuntos a la misma
		segun el protocolo a la clase MensajeProtocolo del objeto.*/
		void serializar_mensaje_creacion_objeto(std::shared_ptr<ObjetoDune> 
		unidad);

		/*Recibe el mapa del juego y agrega la unidad al mapa. Devuelve
		el puntero a la nueva unidad creada.*/
		std::shared_ptr<UnidadMovible> agregar_unidad(Mapa &mapa); 

		/*Recibe un tiempo para reducir el tiempo de entrenamiento
		faltante en caso de que se este entrenando a una unidad. Devuelve
		false si no se esta entrenando una unidad o si no se termino
		de entrenar la que se estaba entrenando. True en caso contrario.*/
		bool avanzar_tiempo_creacion(clock_t tiempo_transcurrido); 
};

#endif
