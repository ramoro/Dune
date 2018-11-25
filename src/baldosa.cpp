#include "baldosa.h"
#include <iostream>

#define VACIA 0
#define OCUPADA 1
#define CODIGO_SALIDA_TERRENO 't'

Baldosa::Baldosa(int estado, Terreno terreno, int &id, std::pair<int,int> esquina): estado(estado), 
terreno(terreno), id(id++), esquina(esquina){
#ifdef NACHO
	//std::cout << "Esquina " << esquina.first << " " << esquina.second << std::endl;
#endif
}

bool Baldosa::poner_objeto(ObjetoDune* objeto_dune) {
	if (estado == OCUPADA) {
		return false;
	} else {
		objeto = objeto_dune;
		estado = OCUPADA;
		return true;
	}
}

std::string Baldosa::obtener_terreno() {
	return terreno.obtener_nombre_material();
}

void Baldosa::sacar_objeto() {
	objeto = NULL;
	estado = VACIA;
}

bool Baldosa::esta_ocupada() {
	if(estado == OCUPADA) return true;
	return false;
}

int Baldosa::obtener_id_objeto_contenido() {
	return objeto->pedir_id();
}

void Baldosa::marcar_como_ocupada() {
	estado = OCUPADA;
}

void Baldosa::marcar_como_desocupada() {
	estado = VACIA;
}

void Baldosa::serializar_mensaje_salida() {
	std::cout << "entro a serializar " << std::endl;
	mensaje.asignar_accion(CODIGO_SALIDA_TERRENO);
	mensaje.agregar_parametro(30);
	mensaje.agregar_parametro(id);
	mensaje.agregar_parametro(10);
	mensaje.agregar_parametro(10);
	mensaje.agregar_parametro(esquina.first);
	mensaje.agregar_parametro(esquina.second);
}