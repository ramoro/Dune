#ifndef COSECHADORA_H
#define COSECHADORA_H

#include "vehiculo.h"
#include <memory>
#include <utility>

class Mapa;
class Vehiculo;

/*Clase que representa una unidad de una cosechadora en el mundo de Dune.
Es la unica unidad que puede recolectar la especia encontrada en las
arenas de Arrakis y llevarla a las refinerías.*/ 
class Cosechadora: public Vehiculo {
	private:
		int especia_encima;
		int extraccion_especia_por_segundo;
		int deposito_especia_por_segundo;
		int limite_especia;
		double contador_segundo; //va acumulando milisegundos hasta que llega
		                         //al segundo y se reinicia
		
	public:
		/*Constructor de la clase.*/
		Cosechadora(int id, int id_duenio, std::pair<int, int> centro,
		 Config &config);

		/*Recibe el mapa y el id del objeto y devuelve todas las unidades
		afectadas por su ataque.*/
		virtual std::vector<ObjetoDune*> atacar_objetivo(Mapa &mapa, 
		int id_objetivo);

		/*Mata a la unidad seteandola como muerta.*/
		virtual void matar();

		/*En caso de tener un ataque al morir lo ejecuta y devuelve
		un vector con los objetos afectados.*/
		virtual std::vector<ObjetoDune*> ataque_al_morir(Mapa &mapa);

		/*Recibe el terrenoa afectar, el mapa del juego y el tiempo pasado 
		dentro del mismo en milisegundos y segun
		el tiempo que paso recolecta una determinada cantidad de especia
		sacandosela al terreno.
		En caso de llegar a su limite de capacidad se setea en el estado
		de movimiento para depositar la especia.*/
		void afectar_terreno(std::shared_ptr<ObjetoDune> terreno,
		Mapa &mapa, double tiempo_transucrrido);

		/*Devuelve la cantidad de especia que extrae en un segundo.*/
		int obtener_extraccion_especia();

		/*Devuelve la cantidad de especia que deposita la cosechadora
		en un segundo. En caso de tener menos que eso devuelve toda
		la especia que tiene encima.*/
		int depositar_especia_en_segundo();

	private:
		/*Busca la refineria mas cercana que tiene la cosechadora dentro
		del mapa recibido.
		Si no hay ninguna la cosechadora queda como inactiva esperando
		otra orden. Si hay alguna se cambia el estado de aquella en 
		movimiento para depositar, almacenandole el terreno al que tiene
		que volver.*/
		void buscar_depositar_especia(Mapa &mapa, 
		std::shared_ptr<ObjetoDune> terreno);
};

#endif

