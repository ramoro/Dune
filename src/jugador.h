#ifndef JUGADOR_H
#define JUGADOR_H

#include <utility>
#include <map>
#include <vector>
#include <memory>
#include "observador.h"
#include "config.h"

class UnidadMovible;
class Edificio;

/*Clase que representa a un jugador.*/
class Jugador {
	private:
		std::map<int, int> edificios_por_tipo;
		int dinero;
		std::string casa;
		int capacidad_especia; //representa todo el espacio que tiene el
								//jugador para guardar especia
		int capacidad_especia_disponible; //representa de todo el espacio
										//que tiene el jugador para guardar
										//especia solo el disponible
		int energia_disponible;
		int id_edificio_entrenando_unidad;

	public:
		/*Constructor de la clase.*/
		Jugador(std::string casa, Config &config);

		/*Recibe un puntero a un objeto Dune. Se lo agregar al jugador
		sacandole el dinero correspondiente.*/
		void agregar_edificio(Edificio* objeto, 
		int id_objeto, std::pair<int, int> centro);

		/*Devuelve true si el edificio se puede agregar al jugador, false
		en caso contrario.*/
		bool agregado_edificio(ObjetoDune* objeto);

		/*Recibe edificio a eliminar y lo elimina
		sacandose el aporte energetico que generaba el edificio.*/
		void eliminar_edificio(std::shared_ptr<Edificio> edificio);

		/*Recibe una determinada cantidad de dinero y se la aumenta al
		jugador.*/
		void aumentar_dinero(int valor);

		/*Recibe un numero con la capacidad de especia a aumentarle al jugador
		y se la aumenta.*/
		void aumentar_capacidad_especia(int capacidad);

		/*Recibe un numero a reducir de capacidad para almacenar
		especias y se lo reduce. Tambien le reduce la capacidad
		disponible, la cual a lo sumo puede quedar en cero, jamas
		en negativo.*/
		void reducir_capacidad_especia(int cap_a_reducir); 

		/*Recibe una puntero a una unidad movible y devuelve true
		si el jugador posee los requisitos para asignarsele esa
		nueva unidad. False en caso contrario.*/
		bool agregada_unidad(UnidadMovible* unidad);

		/*Recibe un valor y se lo resta al dinero del jugador.*/
		void reducir_dinero(int valor);

		/*Devuelve la energia disponible que posee le jugador.
		En caso de devolver un numero negativo significa
		que tiene mas edificios consumiendo energia de los que
		tiene generando.*/
		int pedir_energia_disponible();

		/*Recibe el id de un edificio y se lo asgina al jugador
		como el edificio que actualmente esta entrenando
		una unidad.*/
		void agregar_edificio_entrenando(int id_edificio);

		/*Pone al id del edificio entrenando como -1, que significa
		que no tiene en ese momento ningun edificio entrenando a alguna
		unidad.*/
		void setear_no_entrenando();

		/*Devuelve el id del edificio del jugado que esta entrenando o -1
		en caso de no estar entrenando unidades.*/
		int pedir_id_edificio_entrenando();

		/*Recibe una cantidad de especia y la agrega al jugador.
		Devuelve la cantidad de especia que pudo ser agregada.*/
		int agregar_especia(int cant_especia);
};

#endif 