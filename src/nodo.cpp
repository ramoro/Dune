#include "nodo.h"
#include <vector>
#include <stack>
#include <cmath>
#include <iostream>

#define POSICION_INHABILITADA 1
 
Nodo::Nodo(Nodo *nodo_padre, const std::pair<int,int> &pos) : 
	padre(nodo_padre), posicion(pos) {}

bool Nodo::operator==(const Nodo &otro_nodo) {
	return posicion == otro_nodo.posicion;
}

void Nodo::poner_valor_g(int valor) {
	valor_g = valor;
}

void Nodo::poner_valor_h(int valor) {
	valor_h = valor;
}

int Nodo::obtener_valor_f() {
	return valor_g + valor_h;
}

int Nodo::obtener_valor_g() {
	return valor_g; 
}

Nodo* Nodo::obtener_padre() {
	return padre;
}

std::pair<int, int> Nodo::obtener_posicion() {
	return posicion;
}

Nodo& Nodo::operator=(const Nodo &otro) {	
	if (this == &otro) {
		return *this; 
	}
	valor_g = otro.valor_g;
	valor_h = otro.valor_h;
	this->padre = otro.padre;
	posicion = otro.posicion;
	return *this;
}

Nodo::Nodo(const Nodo &otro) {
	valor_g = otro.valor_g;
	valor_h = otro.valor_h;
	posicion = otro.posicion;
	padre = otro.padre;
}


/*int main() {
	//parametros
	std::pair<int ,int> inicio(0, 0);
	std::vector<std::vector<int>> mapa;
	std::pair<int, int> final(2, 0);
	//fin parametros

	Nodo nodo_inicial(NULL, inicio);
	Nodo nodo_evaluado = nodo_inicial;
  	Nodo nodo_aux = nodo_evaluado;
  	Nodo nodo_nuevo(&nodo_aux, std::pair<int, int>(1,0));

  	nodo_evaluado = nodo_nuevo;
  	Nodo nodo_aux2 = nodo_evaluado;
  	Nodo nodo_nuevo2(&nodo_aux2, std::pair<int, int>(2,0));


}*/