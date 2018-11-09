#ifndef OBJETO_DUNE_H
#define OBJETO_DUNE_H

#include <utility>
#include <vector>

/*Clase abstracta que representa a un objeto del mundo dune que puede
ser tanto un edificio como una unidad movible (vehiculos y 
unidades de ataque).*/
class ObjetoDune {
	private:
		int vida;


	protected:
		int costo_dinero;
		int id;
		int id_tipo;
		int id_duenio;
		int base;
		int altura;
		std::pair<int, int> centro;

	public:
		/*Constructor de la clase.*/
		ObjetoDune(int vida, int costo, int id, int id_duenio, int base, 
		int altura, std::pair<int, int> centro);

		/*Recibe el danio a disminuirle a la vida del objeto y devuelve
		la vida restante que le queda. En caso de devolver 0 o un numero
		negativo significa que la unidad murio/fallecio/se destruyo/caput.*/
		int reducir_vida(int danio);

		/*Devuelve el costo en dinero que conlleva obtener el objeto
		(puede ser el costo que trae construir un edificio o un vehiculo
		o el costo que trae entrenar a una unidad de ataque).*/
		int obtener_costo();

		/*Devuelve el id segun el tipo al que corresponde el objeto.
		Por ejemplo dentro de los edificios todas las Refinerias se 
		identifican con un id.*/
		int pedir_id_tipo();

		/*Devuelve el id unico del objeto.*/
		int pedir_id();

		/*Devuelve el id del jugador que posee el objeto.*/
		int pedir_id_duenio();

		/*Devuelve el ancho del objeto.*/
		int obtener_base();

		/*Devuelve la altura del objeto.*/
		int obtener_altura();

		/*Devuelve el la posicion del centro del objeto.*/
		std::pair<int, int> obtener_centro();

		/*Recibe un id de un jugador y le asigna como duenio
		al objeto el jugador pasado por parametro.*/
		void asignar_duenio(int id_nuevo_duenio);

		/*Recibe una coordenada nueva y se la asigna al centro.*/
		void asignar_centro(std::pair<int, int> centro_nuevo);
};

#endif
