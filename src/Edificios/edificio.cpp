#include "edificio.h"
#include "../observador.h"
#include <iostream>
#include <math.h>

#define INACTIVO 0
#define ENTRENANDO 1
#define DESTRUIDO -1
#define CODIGO_CREACION 'c'
#define CODIGO_PERDIO_DUENIO_EDIFICIO 'e'

Edificio::Edificio(int aporte_energetico, int costo_dinero,
int puntos_estructura, int id, 
int id_duenio, int base, int altura, std::pair<int, int> centro) :
ObjetoDune(puntos_estructura, costo_dinero, id, id_duenio, base, altura,
centro), aporte_energetico(aporte_energetico){
	porcentaje_recuperacion = 0.5;
	estado = INACTIVO;
}

int Edificio::obtener_aporte_energetico() {
	return aporte_energetico;
}

bool Edificio::agregar(Mapa &mapa, Jugador &jugador, int id_edificio, 
int id_tipo_edificio) {
	bool agregar_a_mapa = false;
	bool agregar_a_jugador = false;
	bool agregar_posible = false;
		
	agregar_a_mapa = mapa.agregado_edificio(this);
	agregar_a_jugador = jugador.agregado_edificio(this);
	
	if (agregar_a_mapa && agregar_a_jugador) {
		mapa.agregar_objeto(this, id_edificio, this->centro,true);
		jugador.agregar_edificio(this, id_edificio, this->centro);
		agregar_posible = true;
	}
	return agregar_posible;
}

bool Edificio::agregar_al_juego(Mapa &mapa, Jugador &jugador, int id_edificio, 
int id_tipo_edificio) {
	return true;
}

int Edificio::daniar(UnidadMovible* unidad_atacante, int tiempo_transcurrido) {
	int danio_recibido = unidad_atacante->pedir_danio("edificio", 
	tiempo_transcurrido);
	return ObjetoDune::reducir_vida(danio_recibido);
}

bool Edificio::se_puede_agregar_unidad(Jugador &jugador, 
int id_tipo_unidad, int id_unidad, Config &config) {
	std::pair<int,int> posicion_central(-1,-1);

	std::shared_ptr<UnidadMovible> ptr_unidad = fabrica_unidades_movibles.
	crear_unidad_movible(id_tipo_unidad, id_unidad, this->id_duenio, 
	posicion_central,config);

	/*bool edificio_correcto = false;
	std::vector<int> edificios_necesitados = ptr_unidad->
	obtener_edificios_necesarios();

	for (std::vector<int>::iterator it = edificios_necesitados.begin();
	it != edificios_necesitados.end(); ++it) {
		if (this->id_tipo == *it) {
			edificio_correcto = true;
		}
	}*/

	if (ptr_unidad->se_puede_agregar(jugador)) {
		jugador.reducir_dinero(ptr_unidad->obtener_costo());
		estado = ENTRENANDO;
		unidad_entrenando = ptr_unidad;
		jugador.agregar_edificio_entrenando(this->id);
		return true;
	}
	return false;
}

void Edificio::vender(Jugador &jugador) {
	jugador.aumentar_dinero(this->costo_dinero * 
	this->porcentaje_recuperacion);
	matar();
}

void Edificio::serializar_mensaje_creacion_objeto(
std::shared_ptr<ObjetoDune> objeto) {
	MensajeProtocolo mensaje;
	mensaje.asignar_accion(CODIGO_CREACION);
	mensaje.agregar_parametro(objeto->pedir_id_tipo());
	mensaje.agregar_parametro(objeto->pedir_id());
	mensaje.agregar_parametro(objeto->obtener_base());
	mensaje.agregar_parametro(objeto->obtener_altura());
	mensaje.agregar_parametro((objeto->obtener_centro()).first);
	mensaje.agregar_parametro((objeto->obtener_centro()).second);
	mensaje.agregar_parametro(objeto->pedir_id_duenio());
	mensajes.push_back(std::move(mensaje));

	/*if (objeto->pedir_id_tipo() == 0) {
		mensaje.asignar_accion('t');
		mensaje.agregar_parametro(30);
		mensaje.agregar_parametro(100);
		mensaje.agregar_parametro(500);
		mensaje.agregar_parametro(500);
		mensaje.agregar_parametro(0);
		mensaje.agregar_parametro(0);
		mensajes.push_back(std::move(mensaje));
	}*/
}

std::shared_ptr<UnidadMovible> Edificio::agregar_unidad(Mapa &mapa) {
	std::pair<int, int> pos_central;
	if (!mapa.ubicar_unidad(this->id, pos_central, 
		unidad_entrenando)) {
	}

	unidad_entrenando->set_centro(pos_central);
	unidad_entrenando->agregar(mapa);

	std::shared_ptr<UnidadMovible> unidad_nueva = unidad_entrenando;
	serializar_mensaje_creacion_objeto(unidad_nueva);
	unidad_entrenando = NULL;
	estado = INACTIVO;
	return unidad_nueva;
}

bool Edificio::avanzar_tiempo_creacion(int tiempo_transcurrido) {
	// << "Tiempo transcurrido en ms" << tiempo_transcurrido << std::endl;
	if (estado == INACTIVO) {
		return false;
	} else {
		int tiempo_faltante = unidad_entrenando->
		tiempo_creacion_faltante(tiempo_transcurrido);
		if (tiempo_faltante <= 0) {
			return true;
		}
		return false;
	}
}

void Edificio::matar() {
	estado = DESTRUIDO;
	fuera_de_juego = true;
}

void Edificio::actualizar_existencia(Jugador &jugador) {}

void Edificio::serializar_mensaje_muerte() {
	ObjetoDune::mensaje_muerte();
}

void Edificio::serializar_mensaje_perdio_jugador() {
	MensajeProtocolo mensaje;
	mensaje.asignar_accion(CODIGO_PERDIO_DUENIO_EDIFICIO);
	//agrego cualquier id de jugador mientras que no sea
	//la del duenio del edificio ya que se avisa que otro
	//gano para decirle nomas que perdio
	mensaje.agregar_parametro(this->id_duenio + 1);
	mensajes.push_back(std::move(mensaje));
}

int Edificio::calcular_distancia_baldosas(std::pair<int,int> &centro_otro){
	return sqrt((centro.first - centro_otro.first)*(centro.first - 
		centro_otro.first) + (centro.second - centro_otro.second)*
	(centro.second - centro_otro.second));
}
