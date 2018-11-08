#ifndef JUGADOR_H
#define JUGADOR_H

#include <utility>
#include <map>
#include <vector>
#include <memory>
#include "observador.h"
#include "root.h"

class UnidadMovible;
class Edificio;

/*Clase que representa a un jugador.*/
class Jugador {
	private:
		std::map<int, int> edificios_por_tipo;
		int dinero;
		std::string casa;
		int capacidad_especia;
		int capacidad_especia_disponible;
		int energia_disponible;

	public:
		/*Constructor de la clase.*/
		Jugador(std::string casa, Root &root);

		/*Recibe un puntero a un objeto Dune. Se lo agregar al jugador
		sacandole el dinero correspondiente.*/
		void agregar_edificio(Edificio* objeto, 
		int id_objeto, std::pair<int, int> centro);

		/*Devuelve true si el edificio se puede agregar al jugador, false
		en caso contrario.*/
		bool agregado_edificio(ObjetoDune* objeto);

		/*Recibe objeto/edificio a eliminar y lo elimina
		sacandose el aporte energetico que generaba el edificio.*/
		void eliminar_edificio(Edificio *edificio);

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

	private:
		/*Recibe un valor y se lo resta al dinero del jugador.*/
		void reducir_dinero(int valor);
};

#endif 