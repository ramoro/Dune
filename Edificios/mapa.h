#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include <utility>
#include <map>
#include "objeto_dune.h"
#include "coordenada.h"

/*Clase que representa a un mapa del mundo Dune.*/
class Mapa {
	private:
		std::vector<std::vector<Coordenada>> coordenadas;
		std::map<int, std::pair<ObjetoDune, std::pair<int, int>>>
		mapa_objetos_posiciones;
		//mapa con ids de edificios y su coordenada para ubicarlos rapido ya
		//que el cliente no va a enviar la posicion del edificio

	public:
		/*Agrega un objeto del mundo Dune en el mapa de posiciones segun
		la posicion pasada por parametro. Si la posicion esta ocupada
		no lo agrega y devuelve false. True en caso contrario.*/
		bool agregar_objeto(ObjetoDune objeto, int id_objeto, 
		std::pair<int, int> posicion);

		/*Recibe un par con la coordenada o posicion y se devuelve
		el tipo de terreno que se encuentra en la misma.*/
		std::string pedir_terreno_coordenada(std::pair<int, int> posicion);

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

		Mapa();
};

#endif 