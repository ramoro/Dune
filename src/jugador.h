#ifndef JUGADOR_H
#define JUGADOR_H

#include <utility>
#include <map>
#include <vector>
#include <memory>
#include "Edificios/edificio.h"
#include "UnidadesMovibles/unidad_movible.h"
#include "UnidadesMovibles/raider.h"

/*Clase que representa a un jugador.*/
class Jugador {
	private:
		std::map<int, std::shared_ptr<Edificio>> edificios;
		std::map<int, int> edificios_por_tipo;
		int dinero;
		std::string casa;
		std::map<int, std::shared_ptr<UnidadMovible>> unidades;
		std::map<int, int> unidades_por_tipo;

	public:
		/*Constructor de la clase.*/
		Jugador(std::string casa);

		/*Recibe un puntero a un edificio, el id del edificio y el id
		del tipo de edificio al que corresponde. Se lo agregar al jugador
		en caso de tener el dinero suficiente para crearlo y devuelve true.
		En caso de no alcanzar con el dinero no se lo crea y devuelve false.*/
		bool agregar_edificio(std::shared_ptr<Edificio> edificio, int id_edificio,
		int id_tipo_edificio);

		/*Recibe el id del edificio y el id del tipo del edificio y los usa
		ambos para borrar el edificio tanto del mapa de edificios como del mapa
		que contiene la cantidad de edificios por cada tipo que existe.*/
		void eliminar_edificio(int id_edificio, int id_tipo_edificio);

		void eliminar_unidad(int id_edificio, int id_tipo_edificio);

		/*Recibe una determinada cantidad de dinero y se la aumenta al
		jugador.*/
		void aumentar_dinero(int valor);


		bool agregar_unidad(std::shared_ptr<UnidadMovible> unidad, int id_unidad,
		int id_tipo_unidad);
		/*Recibe el id de la unidad a crear y se fija que exista el edificio requerido
		para poder crear la misma*/
		bool existe_edificio(int id_unidad);

	private:
		/*Recibe un valor y se lo resta al dinero del jugador.*/
		void reducir_dinero(int valor);
};

#endif 