#include "edificio.h"
#include "../observador.h"
#include <iostream>

Edificio::Edificio(int aporte_energetico, int costo_dinero,
int puntos_estructura, int id, 
int id_duenio, int base, int altura, std::pair<int, int> centro) :
ObjetoDune(puntos_estructura, costo_dinero, id, id_duenio, base, altura,
centro), aporte_energetico(aporte_energetico){
	porcentaje_recuperacion = 0.5;
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
	/*if (agregar_posible) {
		for (std::vector<Observador*>::iterator it = observadores.begin();
		it != observadores.end(); ++it) {
			(*it)->agregar_edificio(this, id_edificio, posicion_central);
		}
	}*/
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

void Edificio::destruir(Mapa &mapa, Jugador &jugador) {}

void Edificio::eliminar(Mapa &mapa, Jugador &jugador) {
	mapa.eliminar_objeto(this->id);
	jugador.eliminar_edificio(this);
}

void Edificio::autodemoler(Mapa &mapa, Jugador &jugador) {
	eliminar(mapa, jugador);
	jugador.aumentar_dinero(porcentaje_recuperacion * this->costo_dinero);
}

std::shared_ptr<UnidadMovible> Edificio::agregar_unidad(Mapa &mapa, 
Jugador &jugador, int id_tipo_unidad, int id_unidad) {
	std::pair<int,int> posicion_central(-1,-1);

	std::shared_ptr<UnidadMovible> ptr_unidad = fabrica_unidades_movibles.
	crear_unidad_movible(id_tipo_unidad, id_unidad, this->id_duenio, 
	posicion_central);

	if (!mapa.ubicar_unidad(this->id, posicion_central,
		ptr_unidad->obtener_base(),ptr_unidad->obtener_altura())){
	}

	ptr_unidad->set_centro(posicion_central);

	if (posicion_central.first != -1){
		ptr_unidad->agregar(mapa, jugador);
	}	
	
	return ptr_unidad;
}
