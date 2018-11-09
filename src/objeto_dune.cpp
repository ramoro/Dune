#include "objeto_dune.h"

ObjetoDune::ObjetoDune(int vida, int costo, int id, int id_duenio, int base,
int altura, std::pair<int, int> centro): vida(vida), costo_dinero(costo), 
id(id), id_duenio(id_duenio), base(base), altura(altura), centro(centro) {}

int ObjetoDune::reducir_vida(int danio) {
	vida -= danio;
	return vida;
} 

int ObjetoDune::obtener_costo() {
	return costo_dinero;
}

int ObjetoDune::pedir_id_tipo() {
	return id_tipo;
}

int ObjetoDune::pedir_id() {
	return id;
}

int ObjetoDune::pedir_id_duenio() {
	return id_duenio;
}

int ObjetoDune::obtener_base() {
	return base;
}

int ObjetoDune::obtener_altura() {
	return altura;
}

std::pair<int, int> ObjetoDune::obtener_centro() {
	return centro;
}

void ObjetoDune::asignar_duenio(int id_nuevo_duenio) {
	id_duenio = id_nuevo_duenio;
}

void ObjetoDune::asignar_centro(std::pair<int, int> centro_nuevo) {
	centro = centro_nuevo;
}