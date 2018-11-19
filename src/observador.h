#ifndef OBSERVADOR_H
#define OBSERVADOR_H

#include <utility>
#include <memory>
class ObjetoDune;

/*Clase abstracta que representa un observador. Su existencia se debe
al uso del patron de programacion Observer.*/
class Observador {
	public:
		/*Metodo virtual puro que devuelve true si se puede agregar
		el edificio al observador o false en caso contrario.*/
		virtual bool agregado_edificio(std::pair<int, int>
		posicion_central, ObjetoDune* objeto) = 0;

		virtual bool edificio(std::pair<int, int>
		posicion_central, ObjetoDune* objeto) = 0;
		/*Metodo virtual que agrega el edificio al observador.*/
		/*virtual void agregar_edificio(ObjetoDune* objeto, 
		int id_objeto, ObjetoDune* centro) = 0;*/
};

#endif 