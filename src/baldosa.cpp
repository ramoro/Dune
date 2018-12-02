#include "baldosa.h"
#include <iostream>
#include "UnidadesMovibles/cosechadora.h"
#include "mensaje_protocolo.h"

#define VACIA 0
#define OCUPADA_EDIFICIO 1
#define OCUPADA_UNIDAD 2
#define CODIGO_SALIDA_TERRENO 't'

Baldosa::Baldosa(int estado, Terreno terreno, int id, 
std::pair<int, int> posicion): ObjetoDune(terreno.obtener_cantidad_especia(),
0, id, -1, 1, 1, posicion), estado(estado), 
terreno(terreno) {}

bool Baldosa::poner_edificio(ObjetoDune* objeto_dune) {
	if (estado == OCUPADA_EDIFICIO || estado == OCUPADA_UNIDAD) {
		return false;
	} else {
		objeto = objeto_dune;
		estado = OCUPADA_EDIFICIO;
		return true;
	}
}

bool Baldosa::poner_unidad(ObjetoDune* objeto_dune) {
	if (estado == OCUPADA_EDIFICIO || estado == OCUPADA_UNIDAD) {
		return false;
	} else {
		objeto = objeto_dune;
		estado = OCUPADA_UNIDAD;
		return true;
	}
}

int Baldosa::obtener_terreno() {
	return terreno.obtener_id_material();
}

void Baldosa::sacar_objeto() {
	objeto = NULL;
	estado = VACIA;
}

bool Baldosa::esta_ocupada_edificio() {
	if(estado == OCUPADA_EDIFICIO) return true;
	return false;
}
bool Baldosa::esta_ocupada_unidad() {
	if(estado == OCUPADA_UNIDAD) return true;
	return false;
}
int Baldosa::obtener_id_objeto_contenido() {
	return objeto->pedir_id();
}

void Baldosa::marcar_como_ocupada_edificio() {
	estado = OCUPADA_EDIFICIO;
}

void Baldosa::marcar_como_ocupada_unidad() {
	estado = OCUPADA_UNIDAD;
}

void Baldosa::marcar_como_desocupada() {
	estado = VACIA;
}

void Baldosa::serializar_mensaje_baldosa(int cant_pixeles_baldosa) {
	MensajeProtocolo mensaje;
	mensaje.asignar_accion(CODIGO_SALIDA_TERRENO);
	mensaje.agregar_parametro(terreno.obtener_id_material());
	mensaje.agregar_parametro(id);
	mensaje.agregar_parametro(cant_pixeles_baldosa);
	mensaje.agregar_parametro(cant_pixeles_baldosa);
	mensaje.agregar_parametro(obtener_centro().first);
	mensaje.agregar_parametro(obtener_centro().second);
	std::cout << "Serializo terreno con id " << id << " y tipo " << terreno.obtener_id_material() << std::endl;
	mensajes.push_back(std::move(mensaje));
}

int Baldosa::cantidad_mensajes(){
	//// << mensaje.pedir_accion() << //;
	return mensajes.size();
}

int Baldosa::remover_especia(Cosechadora* unidad_atacante) {
//	std::cout << "Baldosa::remover_especia id "  << id << std::endl;
	return terreno.reducir_especia(unidad_atacante->
	obtener_extraccion_especia());
}

void Baldosa::matar() {
	ObjetoDune::mensaje_muerte();
	fuera_de_juego = true;
}

int Baldosa::obtener_cantidad_especia() {
	return terreno.obtener_cantidad_especia();
}
