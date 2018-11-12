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
		y en la posicion tambien pasada por parametro. Devuelve el ptr
		al edificio si se pudo crear, o null si no.*/
		std::shared_ptr<Edificio> agregar_edificio(int id_jugador, std::pair<int, int>
		posicion_central, int id_tipo_edificio);

		/*Recibe el id del tipo de unidad movible que ataca
		y el id del objeto atacado. Devuelve un vector de pares.
		Cada par con el id de la unidad afectada y la vida que le
		queda luego de ser atacada.*/
		std::vector<std::pair<int, int>> atacar_objeto(
		int id_tipo_unidad_atacante, int id_objeto_atacado);

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

		/*Recibe el id de una unidad y la posicion a donde moverla y devuelve
		un vector con las posiciones que debe seguir la unidad para moverse
		de la mejor manera hacia su destino.*/
		std::vector<std::pair<int, int>> mover_unidad(int id_unidad, 
		std::pair<int, int> posicion_destino);

		/*Devuelve un vector de ints con el id de la unidad comida.*/
		std::vector<int> generar_gusano();

		/*Recibe una determinada cantidad de ticks que pasaron en el juego
		y actualiza el mismo segun ese tiempo transcurrido.*/
		void actualizar_modelo(clock_t tiempo_transcurrido);

		void recibir_comando(std::string comando);

		void split(const std::string& s, char c,
		std::vector<int>& v);

	private:
		/*Metodo recursivo que recibe un vector con el id de los objetos
		afectados por el ataque de una unidad, un puntero al atacante y
		un vector de pares (id, vida restante) que sera llenado con
		los objetos afectados por el ataque.*/
		void ejecutar_ataque(std::vector<int> objetos_afectados, 
		std::shared_ptr<UnidadMovible> atacante, std::vector<std::pair
		<int, int>> &ids_vidas); 
};

#endif 