#ifndef UNIDAD_MOVIBLE_H
#define UNIDAD_MOVIBLE_H

#include "../objeto_dune.h"
#include "../Armas/arma.h"
#include "../jugador.h"
#include "../mapa.h"
#include <string>
#include <vector>
#include <utility>

/*Clase abstracta que representa una unidad movible en el mundo de Dune
que puede ser tanto un vehiculo como una unidad de infanteria.*/
class UnidadMovible: public ObjetoDune {
	private:
		int rango;
		int velocidad; //en km/h
		float tiempo_creacion; //en minutos
		
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
		//virtual std::vector<std::pair<int, int>> matar(Mapa &mapa) = 0;

		/*Recibe el mapa del juego y elimina el objeto del mapa.*/
		void eliminar(Mapa &mapa);

		/*Devuelve un vector con ids de los tipos de edificios que necesita
		la unidad para poder ser creada.*/
		std::vector<int> obtener_edificios_necesarios();

		/*Recibe el mapa del juego y el jugador duenio de la unidad
		y devuelve la posicion donde la unidad fue agregada.
		En caso de no haber podido ser agregada se devuelve un (-1, -1).*/
		std::pair<int, int> agregar(Mapa &mapa, Jugador 
		&jugador);
};

#endif 