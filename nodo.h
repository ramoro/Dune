#ifndef NODO_H
#define NODO_H

#include <utility> 

/*Clase que representa a un Nodo para utilizarse en el algoritmo
A estrella.*/
class Nodo {
	private:
		int valor_g;
		int valor_h;
		Nodo *padre;
		std::pair<int, int> posicion;
		
	public:
		/*Constructor de la clase*/
		Nodo(Nodo *nodo_padre, const std::pair<int,int> &pos);

		/*Sobrecarga del operador equal. Devuelve true si
		ambos nodos tienen igual posicion, false en caso contrario.*/
		bool operator==(const Nodo &otro_nodo);

		/*Recibe un valor y se lo setea al valor_g del objeto Nodo.*/
		void poner_valor_g(int valor);

		/*Recibe un valor y se lo setea al valor_h del objeto Nodo.*/
		void poner_valor_h(int valor);

		/*Devuelve el valor f del nodo.*/
		int obtener_valor_f();

		/*Devielve el valor g del nodo.*/
		int obtener_valor_g();

		/*Devuelve un puntero al nodo padre.*/
		Nodo* obtener_padre();

		/*Devuelve la posicion del nodo.*/
		std::pair<int, int> obtener_posicion();

		Nodo& operator=(const Nodo& otro);

		Nodo(const Nodo &otro);
};

#endif
