#include <cmath>
#include "buscador_mejor_camino.h"
#include "mapa.h"
#include <iostream>
#include <stack>

#define PRECIPICIO 35

//FALTA VERIFICAR QUE EL ESPACIOA DODNE ME MUEVO NO ESTE OCUPADO Y QUE
//SI ES CIMA SOLO PUEDE PASAR UNIDADES DE INFANTERIA
//USAR ALGO COMO DEFINE PARA LAS 8 DIRECCIONES (TYPEDEF SEGUN FEDE)

void BuscadorMejorCamino::delete_vector_nodos(std::vector<Nodo> nodos) {
  for (std::vector<Nodo>::iterator it = nodos.begin(); it != nodos.end();
  ++it) {
    if ((*it).obtener_padre()) {
      delete ((*it).obtener_padre());
    }
  }
}

std::list<std::pair<int, int>> BuscadorMejorCamino::buscar_mejor_camino
(Mapa &mapa, std::pair<int, int> &pos_inicial, 
std::pair<int, int> &pos_final) {
	Nodo nodo_inicio(NULL, pos_inicial);
	nodo_inicio.poner_valor_g(0);
	nodo_inicio.poner_valor_h(0);
	Nodo nodo_final(NULL, pos_final);

	std::vector<Nodo> posibles_nodos;
	std::vector<Nodo> nodos_visitados;

	std::stack<Nodo> camino;

	posibles_nodos.push_back(nodo_inicio);

	while(posibles_nodos.size() > 0) {
		Nodo nodo_evaluado = posibles_nodos[0];
      //<< "atrapado" << nodo_evaluado.obtener_posicion().first << nodo_evaluado.obtener_posicion().second<< std::endl;
		int indice_nodo_evaluado = 0;
		int indice_auxiliar = 0;

		//Me quedo con el nodo de menor valor F
		for (std::vector<Nodo>::iterator it = posibles_nodos.begin(); 
  		it != posibles_nodos.end(); ++it) {
  			if ((*it).obtener_valor_f() < nodo_evaluado.obtener_valor_f()) {
  				nodo_evaluado = (*it);
  				indice_nodo_evaluado = indice_auxiliar;
  			}
  			indice_auxiliar++;
  		}

  		posibles_nodos.erase(posibles_nodos.begin() + indice_nodo_evaluado);
  		nodos_visitados.push_back(nodo_evaluado);

  		//Me fijo si llegue al nodo/posicion final y si es asi obtengo
  		//pila con camino
  		if (nodo_evaluado == nodo_final) {
  			Nodo nodo_actual = nodo_evaluado;
  			while(nodo_actual.obtener_padre() != NULL) {
  				camino.push(nodo_actual);
  				nodo_actual = *(nodo_actual.obtener_padre());
  			}
  			/*while (!camino.empty()) {
  				Nodo nodo = camino.top();
  				// << std::get<0>(nodo.obtener_posicion()) << " " << std::get<1>(nodo.obtener_posicion()) << std::endl;
  				camino.pop();
  			}*/

        delete_vector_nodos(posibles_nodos);
        delete_vector_nodos(nodos_visitados);

  			break;
  		}

  		//Reviso hijos del nodo donde estoy parado para ver cuales faltan
  		//agregar a la lista de caminos posibles
  		std::vector<std::pair<int, int>> direcciones = {{0, 1}, {1, 0}, {-1,0}, 
  		{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {0, -1}};
  		std::vector<Nodo> nodos_hijos;
  		for (std::vector<std::pair<int, int>>::iterator it = direcciones.begin(); 
  		it != direcciones.end(); ++it) {
  			std::pair<int, int> posicion_adyacente((std::get<0>(nodo_evaluado.
  			obtener_posicion())) + it->first, (std::get<1>(nodo_evaluado.
  			obtener_posicion())) + it->second);

  			//Verfico que no se evalue una posicion fuera del mapa
  			if (std::get<0>(posicion_adyacente) > (int)(mapa.
  			pedir_limite_filas_baldosa()) || std::get<0>(posicion_adyacente) < 0 
  			|| std::get<1>(posicion_adyacente) > 
  			(int)(mapa.pedir_limite_columnas_baldosa()) || 
  			std::get<1>(posicion_adyacente) < 0) {
  				continue;
  			} 

  			//Evaluo el terreno y unidad para ver si puede pasar por 
  			//esa posicion
  			if (mapa.pedir_terreno_baldosa(posicion_adyacente) == 
        PRECIPICIO) {
          // << "Precipicio " << posicion_adyacente.first << " " << posicion_adyacente.second << std::endl;
          continue;
        }

        if (mapa.esta_ocupada_baldosa(posicion_adyacente) && 
        posicion_adyacente != pos_final) {
          // << "Esta ocupada " << posicion_adyacente.first << " " << posicion_adyacente.second << std::endl;
          continue;
        }
  			Nodo *nodo_aux = new Nodo(nodo_evaluado);
  			Nodo nodo_nuevo(nodo_aux, posicion_adyacente);
  			nodos_hijos.push_back(nodo_nuevo);
  		}

  		std::vector<Nodo> no_agregados;
  		//Reviso nodos adyacentes, les asigno su valor g, h y f
  		//y los agrego en la lista de posibles nodos
  		for (std::vector<Nodo>::iterator it_hijos = nodos_hijos.begin(); 
  		it_hijos != nodos_hijos.end(); ++it_hijos) {
  			bool no_agregar = false;

  			//Si el nodo esta en dentro de los nodos visitados no lo evaluo
  			for (std::vector<Nodo>::iterator it_visitados = nodos_visitados.
  			begin(); it_visitados != nodos_visitados.end(); ++it_visitados) {
  				if ((*it_visitados) == (*it_hijos)) { 
  					no_agregar = true;
  				}
  			}

  			if (no_agregar) {
  				no_agregados.push_back(*it_hijos);
  				continue;
  			}

  			//G sera la distancia (cantidad de nodos, distancia manhattan)
  			//al nodo de inicio
  			(*it_hijos).poner_valor_g(nodo_evaluado.obtener_valor_g() + 1);
  			//H es una heuristica, es la distancia estimada desde el nodo
  			//evaluado hasta el nodo final (hago: los nodos que me faltan ir
  			//de manera horizontal al cuadrado mas los nodos que me faltan ir
  			//en linea vertical al cuadrado
  			(*it_hijos).poner_valor_h(pow(std::get<0>((*it_hijos).
  			obtener_posicion()) - std::get<0>(nodo_final.obtener_posicion()),2)
  			+ pow(std::get<1>((*it_hijos).obtener_posicion()) - std::get<1>
  			(nodo_final.obtener_posicion()),2));

  			//Si el nodo esta entre los posibles ya tenidos en cuenta
  			//y ademas su valor g es mayor, entonces no se agrega
  			for (std::vector<Nodo>::iterator it_posibles = posibles_nodos.
  			begin(); it_posibles != posibles_nodos.end(); ++it_posibles) {
  				if (((*it_hijos) == (*it_posibles)) && ((*it_hijos).
  				obtener_valor_g() > (*it_posibles).obtener_valor_g())) { 
  					no_agregar = true;
  				}
  			}

  			if (no_agregar) {
  				no_agregados.push_back(*it_hijos);
  				continue;
  			}

  			posibles_nodos.push_back(*it_hijos);
  		}

      delete_vector_nodos(no_agregados);
	}
  std::list<std::pair<int, int>> lista_camino;
  while (!camino.empty()) {
    lista_camino.emplace_back((camino.top()).obtener_posicion());
    camino.pop();
  }
	return lista_camino;
}