#include "edificio.h"
#include "../observador.h"
#include <iostream>

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
		mapa.agregar_objeto(this, id_edificio, this->centro);
		jugador.agregar_edificio(this, id_edificio, this->centro);
		agregar_posible = true;
	}
	return agregar_posible;
}

bool Edificio::agregar_al_juego(Mapa &mapa, Jugador &jugador, int id_edificio, 
int id_tipo_edificio) {
	return true;
}

int Edificio::daniar(std::shared_ptr<UnidadMovible> unidad_atacante) {
	int danio = unidad_atacante->pedir_danio("edificio");
	return ObjetoDune::reducir_vida(danio);
}

void Edificio::autodemoler(Mapa &mapa, Jugador &jugador) {
	//eliminar(mapa, jugador);
	jugador.aumentar_dinero(porcentaje_recuperacion * this->costo_dinero);
}

bool Edificio::se_puede_agregar_unidad(Jugador &jugador, 
int id_tipo_unidad, int id_unidad, Root &root) {
	std::pair<int,int> posicion_central(-1,-1);

	std::shared_ptr<UnidadMovible> ptr_unidad = fabrica_unidades_movibles.
	crear_unidad_movible(id_tipo_unidad, id_unidad, this->id_duenio, 
	posicion_central,root);

	if (ptr_unidad->se_puede_agregar(jugador)) {
		jugador.reducir_dinero(ptr_unidad->obtener_costo());
		estado = ENTRENANDO;
		unidades_entrenando.emplace_back(ptr_unidad);
		return true;
	}
	return false;
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
}

std::shared_ptr<UnidadMovible> Edificio::agregar_unidad(Mapa &mapa) {
	std::pair<int, int> pos_central;
	if (!mapa.ubicar_unidad(this->id, pos_central, 
		unidades_entrenando.front()->obtener_base(), 
		unidades_entrenando.front()->obtener_altura())) {
	}

	unidades_entrenando.front()->set_centro(pos_central);

	unidades_entrenando.front()->agregar(mapa);

	std::shared_ptr<UnidadMovible> unidad_nueva = unidades_entrenando.front();
	serializar_mensaje_creacion_objeto(unidad_nueva);
	unidades_entrenando.pop_front();
	if (unidades_entrenando.empty()) {
		estado = INACTIVO;
	}
	return unidad_nueva;
}

bool Edificio::avanzar_tiempo_creacion(double tiempo_transcurrido) {
	if (estado == INACTIVO) {
		return false;
	} else {
		int tiempo_faltante = unidades_entrenando.front()->
		tiempo_creacion_faltante(tiempo_transcurrido);
		if (tiempo_faltante <= 0) {
			return true;
		}
		return false;
	}
}

void Edificio::matar() {
	estado = DESTRUIDO;
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