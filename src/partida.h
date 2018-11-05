#ifndef PARTIDA_H
#define PARTIDA_H

#include <utility>
#include <map>
#include <vector>
#include "jugador.h"
#include "mapa.h"
#include "Edificios/fabrica_edificios.h"
#include "UnidadesMovibles/fabrica_unidades_movibles.h"
#include "buscador_mejor_camino.h"

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
		BuscadorMejorCamino buscador_mejor_camino;

	public:
		/*Constructor de la clase.*/
		Partida();

		/*Recibe un string con un nombre y agregar a la partida un Jugador
		con ese nombre.*/
		void agregar_jugador(std::string nombre_jugador);

		/*Agrega un edificio segun el id de tipo pasado, asociado al id pasado
		por parametro, asignado al jugador con el id pasado por parametro 
		y en la posicion tambien pasada por parametro. Devuelve true si se pudo
		ubicar el edificio. False en caso contario.*/
		bool agregar_edificio(int id_jugador, std::pair<int, int>
		posicion_central, int id_tipo_edificio);

		/*Recibe el id del jugador atacado, el id del tipo de unidad movible que ataca
		y el id del objeto atacado. Devuelve el danio provocado por la unidad o en 
		caso de destruir el objeto devuelve un 0. Si devuelve un -1 significa
		que el objeto no puede atacar.*/
		int atacar_objeto(int id_jugador_atacado, int id_tipo_unidad_atacante, 
		int id_objeto_atacado);

		/*Recibe un id de un edificio. Elimina el 
		edificio y le devuelve al jugador con el id recibido un porcentaje
		del dinero que le costo.*/
		void autodemoler_edificio(int id_edificio);

		/*Recibe el id del tipo de unidad a crear y el id del edificio que
		creara a la unidad y devuelve un par(id_unidad_creada, 
		posicion_central). En caso de no haberse podido crear la unidad
		se devolvera (-1, (-1, -1)).*/
		std::pair<int, std::pair<int,int>> agregar_unidad_movible(
		int id_tipo_unidad, int id_edificio);

		/*Devuelve un vector de pares de ints con el id de la unidad comida y
		el id del jugador duenio de la unidad.*/
		std::vector<std::pair<int, int>> generar_gusano();
};

#endif 