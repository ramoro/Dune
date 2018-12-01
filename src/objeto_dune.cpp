#include "objeto_dune.h"
#include "UnidadesMovibles/unidad_movible.h"
#include "UnidadesMovibles/cosechadora.h"
#include <iostream>

#define CODIGO_MUERTE 'd'

ObjetoDune::ObjetoDune(int vida, int costo, int id, int id_duenio, int base,
int altura, std::pair<int, int> centro): vida(vida), costo_dinero(costo), 
id(id), id_duenio(id_duenio), base(base), altura(altura), centro(centro) {
	fuera_de_juego = false;
}

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

void ObjetoDune::set_centro(std::pair<int, int> centro_nuevo) {
	centro = centro_nuevo;
}

int ObjetoDune::daniar(UnidadMovible* unidad_atacante, 
int tiempo_transcurrido) {
	std::cout << "entro en daniar de objeto dune" << std::endl;
	return 0;
}

void ObjetoDune::matar() {
	std::cout << "Asdas" << std::endl;
}

void ObjetoDune::mensaje_muerte() {
	MensajeProtocolo mensaje;
	mensaje.asignar_accion(CODIGO_MUERTE);
	mensaje.agregar_parametro(this->id);
	mensajes.push_back(std::move(mensaje));
}

std::vector<MensajeProtocolo> ObjetoDune::obtener_mensajes_para_mandar() {
	return mensajes;
}

void ObjetoDune::limpiar_lista_mensajes() {
	mensajes.clear();
}

bool ObjetoDune::esta_fuera_de_juego() {
	return fuera_de_juego;
}
int ObjetoDune::remover_especia(Cosechadora* cosechadora) {
	std::cout << "entreo a remover especia de objeto dune" << std::endl; 
	return 0;
}
int ObjetoDune::obtener_cantidad_especia() {
	std::cout << "entreo a remover especia de objeto dune" << std::endl; 
	return 0;
}