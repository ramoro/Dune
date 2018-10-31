#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include <utility>
#include <map>
#include <string>
#include <memory>
#include "objeto_dune.h"
#include "coordenada.h"

/*Clase que representa a un mapa del mundo Dune.*/
class Mapa {
	private:
		std::vector<std::vector<Coordenada>> coordenadas;
		std::map<int, ObjetoDune> mapa_ids_objetos;
		//mapa con ids de objetos y su coordenada de centro para ubicarlos rapido 
		//ya que el cliente no va a enviar la posicion del edificio

	public:
		/*Recibe una posicion central de un objeto, su base y su altura y se fija
		si los puntos que lo rodean son del terreno pasado como string.
		Devuelve true en caso de que el terreno que ocupa el objeto sea del
		terreno pasado, false en caso contrario.*/
		bool verificar_terreno_alrededores(std::pair<int, int> centro, 
		int altura, int base, std::string terreno);

		/*Agrega un objeto del mundo Dune en el mapa de posiciones segun
		la posicion central pasada por parametro. Si la posicion esta ocupada
		o los alrededores ocupados por el edificio
		no lo agrega y devuelve false. True en caso contrario.*/
		bool agregar_objeto(std::shared_ptr<ObjetoDune> objeto, 
		int id_objeto, std::pair<int, int> centro);

		/*Recibe el danio y el id del objeto a ser daniado. En caso de
		ser aniquilado se devuelve true. False en caso contario.*/
		bool daniar_objeto(int danio, int id_objeto);

		/*Recibe el id del objeto y lo elimina tanto del mapa
		de ids de cada objeto junto con su posicion y de la coordenada
		donde se encuentra ubicado.*/
		void eliminar_objeto(int id_objeto);

		/*Recibe una id de un objeto y devuelve el id del tipo al que
		pertenece.*/
		int pedir_id_tipo_objeto(int id_objeto);

		/*Recibe el id de un objeto y devuelve su posicion en el mapa.*/
		std::pair<int, int> obtener_posicion_objeto(int id_objeto);

		/*Recibe el id de un objeto y devuelve la cantidad de dinero
		que conlleva producirlo.*/
		int pedir_costo_objeto(int id_objeto);

		/*Elige un lugar random para hacer emerger al gusano de arena
		y devuelve un vector con pares de lista (id unidad comida, id duenio de
		la unidad).*/
		std::vector<std::pair<int, int>> desenterrar_gusano();

		/*Devuelve la posicion maxima a la que llega el vector de filas.*/
		unsigned int pedir_limite_filas();

		/*Devuelve la posicion maxima a la que llegan los vectores de
		columnas.*/
		unsigned int pedir_limite_columnas();

		/*Recibe una posicion y devuelve el nombre del terreno de la 
		Coordenada con esa posicion.*/
		std::string pedir_terreno_coordenada(std::pair<int, int> posicion);

		Mapa();

	private:
		/*Recibe el centro de un objeto junto con su base y altura y devuelve
		un vector con el id de los objetos que se encuentran a su alrededor
		junto con el id del jugador que posee ese objeto.*/
		std::vector<std::pair<int, int>> buscar_objetos_en_alrededores(
		std::pair<int, int> centro_objeto1, int base_objeto1, 
		int altura_objeto1);
};

#endif 
