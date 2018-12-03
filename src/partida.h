#ifndef PARTIDA_H
#define PARTIDA_H

#include <utility>
#include <map>
#include <vector>
#include <set>
#include "jugador.h"
#include "mapa.h"
#include "Edificios/fabrica_edificios.h"
#include "UnidadesMovibles/fabrica_unidades_movibles.h"
#include "config.h"
#include "cola_bloqueante.h"

/*Clase que representa a una partida de Dune.*/
class Partida {
	private:
		Mapa mapa;
		std::map<int, Jugador> jugadores;
		std::map<int, std::shared_ptr<Edificio>> edificios;
		std::map<int, std::shared_ptr<UnidadMovible>> unidades_movibles;
		FabricaEdificios fabrica_edificios;
		FabricaUnidadesMovibles fabrica_unidades_movibles;
		int contador_ids_objetos;
		Config config;

	public:
		/*Constructor de la clase.*/
		Partida();

		/*Recibe el id de una casa y el id de un jugador y le asigna esa casa
		al jugador.*/
		void asignar_casa_a_jugador(int id_casa, int id_jugador);

		/*Recibe un id de un jugador con el id de la casa a la que peretenecera
		a la que pertenece y agrega a la partida un Jugador
		con ese id, ademas crea su edificio Centro de Construccion. */
		void agregar_jugador(int id_jugador,
		std::map<int, std::shared_ptr<ColaBloqueante>> cola_mensajes);

		/*Agrega un edificio segun el id de tipo pasado, asociado al id pasado
		por parametro, asignado al jugador con el id pasado por parametro 
		y en la posicion tambien pasada por parametro. En caso de no poder
		agregarse se encola un mensaje respetando el protocolo dentro de
		la cola recibida.*/
		void agregar_edificio(int id_jugador, std::pair<int, int>
		posicion_central, int id_tipo_edificio, 
		std::map<int, std::shared_ptr<ColaBloqueante>> cola_mensajes);

		/*Recibe el id del tipo de unidad movible que ataca
		y el id del objeto atacado. Setea la unidad atacante en modo
		de movimiento para atacar en caso de no estar lo suficientemente
		lejos o en modo ataque.*/
		void atacar_objeto(int id_tipo_unidad_atacante, 
		int id_objeto_atacado);

		/*Recibe el id del tipo de unidad a crear, el id del edificio que
		creara a la unidad y el id del duenio del edificio. Se fija si puede 
		crearla y si no se puede arma el mensaje correspondiente encolandolo
		a la cola recibida.*/
		void iniciar_entrenamiento_unidad_movible(int id_tipo_unidad,
		int id_edificio, int id_jugador, 
		std::map<int, std::shared_ptr<ColaBloqueante>> cola_mensajes);

		/*Recibe el id de una unidad y la posicion a donde moverla y setea
		a la unidad con el mejor camino para empezar a moverse hacia la
		posicion de destino.*/
		void comenzar_movimiento_unidad(int id_unidad, 
		std::pair<int, int> posicion_destino);

		/*Recibe un id de un edificio y lo destruye dandole de vuelta
		al jugador una fraccion del dinero que le costo ese edificio.
		Recibe tambien las colas de mensajes donde encolara el mensaje
		del cambio de dinero.*/
		void vender_edificio(int id_edificio,
		std::map<int, std::shared_ptr<ColaBloqueante>> colas_mensajes);

		/*Recibe el id del tipo del objeto rechazado y el id del
		jugador que intento crearlo y se genera un mensaje
		asginandole la accion de rechazo junto con sus parametros segun
		indica le protocolo y lo encola a la cola recibida.*/
		void serializar_mensaje_rechazo_creacion(
		std::map<int, std::shared_ptr<ColaBloqueante>> cola_mensajes,
		int id_tipo_objeto_rechazado, int id_jugador);

		/*Recibe el dinero actual del jugador, su id y crea un mensaje 
		asigandole la accion de cambio de dinero junto con sus parametros 
		segun indica el protocolo y lo encola a la cola que le corresponde.*/
		void serializar_mensaje_dinero(int dinero, int id_jugador,
		std::map<int, std::shared_ptr<ColaBloqueante>> colas);

		/*Recibe la energia actual del jugador y su id y crea un mensaje
		asigandole la accion de cambio de dinero junto con sus parametros 
		segun indica el protocolo y lo encola a la cola correspondiente.*/
		void serializar_mensaje_energia(int energia, int id_jugador,
		std::map<int, std::shared_ptr<ColaBloqueante>> colas);

		/*Recibe el id de un jugador y elimina todos sus objetos dentro
		de la partida, encolando los mensajes de muerte en las colas
		recibidas.*/
		void eliminar_jugador(int id_jugador,
		std::map<int, std::shared_ptr<ColaBloqueante>> colas);

		/*Recibe una determinada cantidad de tiempo que pasa en el juego
		y lo actualiza segun cuanto transcurrio, agregando los mensajes
		correspondientes a la cola bloqueante recibida por parametro.*/
		void actualizar_modelo(int tiempo_transcurrido, 
		std::map<int, std::shared_ptr<ColaBloqueante>> cola_mensajes);
		
		/*Metodo para llamar a su igual pero de la clase mapa*/
		void terreno_inicial(std::map<int,
		 std::shared_ptr<ColaBloqueante>> cola_mensajes);

		/*Devuelve la cantidad de filas que tiene el mapa*/
		int obtener_limite_mapa_fila();

		/*Devuelve la cantidad de columnas que tiene el mapa*/
		int obtener_limite_mapa_columna();
		
	private:
		/*Recibe el puntero al edificio a actualizar el tiempo de entenamiento
		y el tiempo pasado.*/
		void actualizar_creacion_unidades(std::shared_ptr<Edificio> 
		edificio, int tiempo_transcurrido);

		/*Recibe un puntero a un edificio y lo elimina completamente del 
		juego, encolando el mensaje de cambio de energia en la cola
		recibida.*/
		void eliminar_edificio_del_juego(std::shared_ptr<Edificio> 
		edificio_a_remover, std::map<int, std::shared_ptr<ColaBloqueante>> 
		cola_mensajes);

		/*Recibe un puntero a una unidad y lo elimina completamente del 
		juego.*/
		void eliminar_unidad_del_juego(std::shared_ptr<UnidadMovible> 
		unidad_a_remover);

		/*ubica centro de construccion segun el numero de jugador que sea*/
		std::pair<int,int> ubicar_centro_construccion(int id_jugador);

		/*busca en que parte de cada esquina colocar el centro de construccion
		dada una esquina, devuelve el centro donde puede colocarse*/
		std::pair<int,int> buscar_ubicacion(std::pair<int,int> esquina);

		/*Devuelve true si la posicion_central tiene un edificio cercano aliado
		dentro del rango definido, false en caso contrario. En caso de que no
		existan edificios aliados devuelve true */
		bool esta_dentro(int id_jugador, std::pair<int,int> &posicion_central);

		/*Recibe un vector de colas y un mensaje y lo encola en cada cola.*/
		void guardar_mensaje_en_colas(
		std::map<int, std::shared_ptr<ColaBloqueante>> colas, 
		MensajeProtocolo mensaje);

		/*Recibe un set con puntero a edificios y otro con punteros a unidades
		movibles y elimina de la partida cada uno de ellos.*/
		void eliminar_objetos_de_sets(std::set<std::shared_ptr<Edificio>> 
		&edificios_a_eliminar, std::set<std::shared_ptr<UnidadMovible>> 
		&unidades_a_eliminar, std::map<int, std::shared_ptr<ColaBloqueante>> 
		colas);

		/*Recibe dos sets a los cuales se les agregaran los edificios y 
		unidades movibles a eliminar del jugador con la id recibida
		por parametro. Se encolara a las colas recibidas los mensajes
		de muerte de estos objetos.*/
		void agregar_objetos_a_eliminar(std::set<std::shared_ptr<Edificio>> 
		&edificios_a_eliminar, std::set<std::shared_ptr<UnidadMovible>> 
		&unidades_a_eliminar, int id_duenio_objetos, 
		std::map<int, std::shared_ptr<ColaBloqueante>> colas);

		/*Recibe el id de un objeto muerto y crea un mensaje
		asigandole la accion muerte junto con sus parametros 
		segun indica el protocolo y lo encola a las colas recibidas.*/
		void serializar_mensaje_muerte(int id_objeto_a_remover, 
		std::map<int, std::shared_ptr<ColaBloqueante>> &colas);
};

#endif 
