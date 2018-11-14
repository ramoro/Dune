#ifndef UNIDAD_MOVIBLE_H
#define UNIDAD_MOVIBLE_H

#include "../objeto_dune.h"
#include "../Armas/arma.h"
#include "../jugador.h"
#include "../mapa.h"
#include <string>
#include <vector>
#include <utility>
#include <memory>

class Estado;

/*Clase abstracta que representa una unidad movible en el mundo de Dune
que puede ser tanto un vehiculo como una unidad de infanteria.*/
class UnidadMovible: public ObjetoDune {
	private:
		int rango;
		int velocidad; //en km/h
		float tiempo_creacion; //en segundos
		std::vector<std::pair<int, int>> camino; //esto deberia ser un vector de BALDOSAS
		std::shared_ptr<Estado> estado;
		
	protected:
		std::vector<Arma> armas;
		int rango_ataque_fila;
		int rango_ataque_columna;
		std::vector<int> ids_tipos_edificios_necesarios;

	public:
		/*Constructor de la clase.*/
		UnidadMovible(int rango, int velocidad, 
		float tiempo_creacion, int costo_dinero, int vida, 
		int id, int id_duenio, int base, int altura, std::pair<int, int> 
		centro);

		/*Recibe un string con el objetivo al que esta atacando
		la unidad y devuelve el danio que le realiza al objetivo.*/
		int pedir_danio(std::string objetivo);

		/*Recibe el mapa y el id de un objetivo a atacar y 
		hace que la unidad se acerque al objetivo y ataque.*/
		std::vector<int> atacar(Mapa &mapa, int id_objetivo);

		/*Recibe el mapa del juego y el jugador duenio de la unidad, ademas
		de el id del objeto a atacar. Devuelve un vector de enteros con los
		objetos afecta.*/ 
		virtual std::vector<int> atacar_objetivo(Mapa &mapa, 
		int id_objetivo) = 0;

		/*Metodo virtual puro que dania a la unidad apuntada por el puntero
		recibido.*/
		virtual int daniar(std::shared_ptr<UnidadMovible> unidad_atacante) = 0;

		/*Metodo virtual puro que mata a la unidad movible y la saca del juego.*/
		virtual std::vector<int> matar(Mapa &mapa) = 0;

		//virtual std::vector<int> matar(Mapa &mapa, Root &root) = 0;

		/*Recibe el mapa del juego y elimina el objeto del mapa.*/
		void eliminar(Mapa &mapa);

		/*Devuelve un vector con ids de los tipos de edificios que necesita
		la unidad para poder ser creada.*/
		std::vector<int> obtener_edificios_necesarios();

		/*Recibe el jugador duenio de la unidad y devuelve true si se puede
		agregar la nueva unidad al jugador. False en caso contrario.*/
		bool se_puede_agregar(Jugador &jugador); 

		/*Recibe el mapa del juego y agrega la nueva unidad al juego.*/
		void agregar(Mapa &mapa);

		/*Recibe una cantidad de segundos y se la disminuye 
		al tiempo de creacion. Devuelve el tiempo de creacion
		faltante para crear la unidad luego de haber disminuido los
		segundos recibidos.*/
		int tiempo_creacion_faltante(int segs);

		/*Le asigna el camino a seguir a la unidad y setea su estado
		en movimiento.*/
		void empezar_a_caminar(std::vector<std::pair<int, int>> 
		camino_a_seguir);

		/*Recibe el tiempo transcurridoy el mapa del juego
		y segun el estado en el que se encuentre le objeto lo actualiza.*/
		void actualizar_unidad(clock_t tiempo_transcurrido, 
		Mapa &mapa);
};

#endif 