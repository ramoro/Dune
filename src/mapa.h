#ifndef MAPA_H
#define MAPA_H

#include <vector>
#include <utility>
#include <map>
#include <string>
#include <memory>
#include "objeto_dune.h"
#include "coordenada.h"
#include "observador.h"

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
		bool verificar_terreno_alrededor(std::pair<int, int> centro, 
		int altura, int base, std::string terreno, bool gusano);

		/*Recibe la posicion central de un objeto, su altura y base y devuelve
		un vector con el id de las unidades que se encuentran en su alrededor
		(tienen su centro dentro del rango que abarca la base y la altura
		pasadas). En caso de que verificar_asentamiento sea true apenas
		encontrada una unidad se corta el for ya que para los edificios
		con encontrar una unidad basta.*/
		std::vector<int> buscar_unidades_alrededor(std::pair<int, int>
		centro_unidad, int altura, int base, bool verificar_asentamiento);

		/*Agrega un objeto del mundo Dune en el mapa de posiciones segun
		la posicion central pasada por parametro y su id.*/
		void agregar_objeto(ObjetoDune* objeto, 
		int id_objeto, std::pair<int, int> &centro);

		/*Recibe el id del objeto y lo elimina tanto del mapa
		de ids de cada objeto junto con su posicion y de la coordenada
		donde se encuentra ubicado.*/
		void eliminar_objeto(int id_objeto);

		/*Recibe una id de un objeto y devuelve el id del tipo al que
		pertenece.*/
		int pedir_id_tipo_objeto(int id_objeto);

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

		/*Recibe un puntero al objeto.
		Devuelve true si el objeto se puede agregar al mapa,
		false en caso contrario.*/
		bool agregado_edificio(ObjetoDune* objeto);

		/*Reibe un puntero al objeto, su id y el centro y lo agrega al mapa.*/
		/*void agregar_edificio(ObjetoDune*  objeto, 
		int id_objeto, std::pair<int, int> &centro);*/

		/*Recibe el id de un objeto y el id de otro y mide su distancia, o
		cercania de coordenadas. Devuelve esta cercania en valor absoluto.*/
		std::pair<int,int> pedir_cercania(int id, int id_objetivo);

		/*Recibe el id de la unidad a cambiar y el id del duenio o jugador
		a asignarle y se lo asigna.*/
		void cambiar_equipo(int id_unidad_a_cambiar, int id_nuevo_duenio);

		/*Recibe el id del edificio seleccionado que va a crear las unidades,
		y la posicion donde va a guardar el centro de la unidad creada. 
		Devuelve true o false si encontro una posicion valida para crear la
		unidad alrededor del edificio*/
		bool ubicar_unidad(int id_edificio, std::pair<int, int> 
		&centro_unidad);

		/*Devuelve true si coordenada en la posicion pasada esta ocupada*/
		bool esta_ocupada_coordenada(std::pair<int, int> posicion);

		Mapa();

	private:
		/*Recibe la posicion central de un objeto, su base y su altura y
		setea en ocupadas a todas las coordenadas que ocupa.
		Precondicion:el objeto puede ser agregado.*/
		void marcar_estado_coordenadas_alrededor(std::pair<int, int> 
		pos_central, int altura, int base, bool ocupar);

		/*Devuelve true si encontro una posicion valida para poner la unidad.
		Lo que hace es recorrer horizontalmente hacia la derecha desde la pos 
		inicial pasada hasta el rango que se establece buscando un espacio 
		donde pueda meter una unidad de un tamanio con la base pasada.*/
		bool recorrer_horizontal(std::pair<int, int> &pos_inicial, int rango,
		int base);
		
		/*Devuelve true si encontro una posicion valida para poner la unidad.
		Lo que hace es recorrer verticalmete hacia arriba desde la pos inicial 
		pasada hasta el rango que se establece buscando un espacio donde pueda 
		meter una unidad de un tamanio con la base pasada.*/
		bool recorrer_vertical(std::pair<int, int> &pos_inicial, int rango,
		int altura);
};

#endif 
