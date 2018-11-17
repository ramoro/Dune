#ifndef PARTIDA_H
#define PARTIDA_H

#include <utility>
#include <map>
#include <vector>
#include "jugador.h"
#include "mapa.h"
#include "Edificios/fabrica_edificios.h"
#include "UnidadesMovibles/fabrica_unidades_movibles.h"
#include "root.h"

/*Clase que representa a una partida de Dune.*/
class Partida {
	private:
		Mapa mapa;
		std::map<int, Jugador> jugadores;
		std::map<int, std::shared_ptr<Edificio>> edificios;
		std::map<int, std::shared_ptr<UnidadMovible>> unidades_movibles;
		FabricaEdificios fabrica_edificios;
		FabricaUnidadesMovibles fabrica_unidades_movibles;
		int contador_ids_jugadores;
		int contador_ids_objetos;
		Root root;

	public:
		/*Constructor de la clase.*/
		Partida();

		/*Recibe un string con un nombre y agregar a la partida un Jugador
		con ese nombre.*/
		void agregar_jugador(std::string nombre_jugador);

		/*Agrega un edificio segun el id de tipo pasado, asociado al id pasado
		por parametro, asignado al jugador con el id pasado por parametro 
		y en la posicion tambien pasada por parametro.*/
		void agregar_edificio(int id_jugador, std::pair<int, int>
		posicion_central, int id_tipo_edificio);

		/*Recibe el id del tipo de unidad movible que ataca
		y el id del objeto atacado. Setea la unidad atacante en modo
		de movimiento para atacar en caso de no estar lo suficientemente
		lejos o en modo ataque.*/
		void atacar_objeto(int id_tipo_unidad_atacante, 
		int id_objeto_atacado);

		/*Recibe un id de un edificio. Elimina el 
		edificio y le devuelve al jugador con el id recibido un porcentaje
		del dinero que le costo.*/
		void autodemoler_edificio(int id_edificio);

		/*Recibe el id del tipo de unidad a crear y el id del edificio que
		creara a la unidad. Se fija si puede crearla y dependiendo la situacion
		manda se arma el mensaje correspondiente.*/
		void iniciar_entrenamiento_unidad_movible(
		int id_tipo_unidad, int id_edificio);

		/*Recibe el id de una unidad y la posicion a donde moverla y setea
		a la unidad con el mejor camino para empezar a moverse hacia la
		posicion de destino.*/
		void comenzar_movimiento_unidad(int id_unidad, 
		std::pair<int, int> posicion_destino);

		/*Recibe una determinada cantidad de tiempo que pasa en el juego
		y lo actualiza segun cuanto transcurrio, agregando los mensajes
		correspondientes a la cola bloqueante.*/
		void actualizar_modelo(double tiempo_transcurrido);
		
	private:
		/*Recibe el puntero al edificio a actualizar el tiempo de entenamiento
		y el tiempo pasado.*/
		void actualizar_creacion_unidades(std::shared_ptr<Edificio> 
		edificio, double tiempo_transcurrido);

		/*Recibe un puntero a un edificio y lo elimina completamente del 
		juego.*/
		void eliminar_edificio_del_juego(std::shared_ptr<Edificio> 
		edificio_a_remover);

		/*Recibe un puntero a una unidad y lo elimina completamente del 
		juego.*/
		void eliminar_unidad_del_juego(std::shared_ptr<UnidadMovible> 
		unidad_a_remover);

};

#endif 
